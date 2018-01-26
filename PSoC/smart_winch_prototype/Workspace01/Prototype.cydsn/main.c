/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdio.h>
#include "project.h"
#include "pid.h"
#include "motor.h"
#include "modbusRTU.h"
#include "modbus_regs.h"
#include "millis.h"
#include "nRF24_Adapter.h"


float motor_pwm, setpoint, pid_fb;
const uint8_t nrfAdd[] = {0x01, 0x23, 0x45, 0x67, 0x89};
uint8_t dataToSend[] = {0,1};

extern volatile nrf_irq nRF24_Adapter_Flags;

uint8_t mode_tx = 1;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Write(0); //on board led off
    
    //init nRF24L01 module
    nRF24_Adapter_Start();
    nRF24_set_tx_address(nrfAdd, 5);
    nRF24_set_rx_pipe_0_address(nrfAdd, 5);
    
    
    //used mainly for modbus
    USB_UART_Start();
    
    //for current measurement
    ADC_Start();
    ADC_StartConvert();
    
    //arduino-like millis
    Millis_Start();
           
    QuadDec_Start(); //quadrature decoder module (to sense cable distance)
    QuadDec_WriteCounter(0x8000); //reset measure cable distance (it resets to 32768)
        
    Motor_Start();            
    
    PID_Init();
    PID_Set_Setpoint(&setpoint); //set the address of setpoint variable
    PID_Set_Input(&pid_fb); //set the address of feedback variable
    PID_Set_Output(&motor_pwm); //set the address of output variable
    PID_Set_Output_Limits(-32767, 32767); //pwm resolution reduced to 15-bits due to acoustic noise
    
    PID_ISR_StartEx(PID_Tick); //pid ticker routine is defined in pid.c
    PID_Tick_Timer_Start(); //start 12.5Hz PID timer 
      
    //reset setpoint on startup
    modbus_holding_regs[PID_Setpoint] = 0;
    
    //Enable Watchdog
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
    
    //Find the reset source
    //0     = master reset
    //1     = wdt reset
    //8     = program fault reset
    //16    = software reset
    modbus_holding_regs[Reset_Source] = CySysGetResetReason(CY_SYS_RESET_WDT | CY_SYS_RESET_PROTFAULT | CY_SYS_RESET_SW);
    
    uint8_t rcv[32];
    char tmt[32];
    char tmt1[] = "whynot\r\n";
    char tmt2[] = "transmited\r\n";
    
    
    if(mode_tx) //tx   
    {
        nRF24_set_mode(NRF_MODE_TX);
        nRF24_set_tx_mode();
        nRF24_set_channel(120);
        nRF24_stop_listening();  
    }
    else //rx   
    {
        nRF24_set_mode(NRF_MODE_RX);
        nRF24_set_rx_mode();
        nRF24_set_channel(120);
        nRF24_start_listening();
    }
    
    for(;;)
    {
        //Feed the dog (512ms)
        CySysWatchdogFeed(CY_SYS_WDT_COUNTER0);
        
        
        if(mode_tx) //tx
        { 
            CyDelay(100);
            uint8_t stat = nRF24_get_status();
            
            if (!nRF24_is_tx_fifo_full())
            {
                nRF24_transmit(dataToSend, 2); 
            }
            else
            {
                nRF24_reuse_last_transmitted_payload();
                sprintf(tmt, "retransmitting packet\r\n");                 
                USB_UART_SpiUartPutArray(tmt, sizeof(tmt));
                nRF24_clear_irq_flag(NRF_MAX_RT_IRQ); //acknowledge failed retransmission
            }
                
            //if transmit sucessful
            if(NRF_STATUS_TX_DS_MASK & nRF24_get_status())
            {
                LED_Write(~LED_Read());
                
                dataToSend[0]+=1;
                dataToSend[1]+=1;
                
                nRF24_clear_irq_flag(NRF_TX_DS_IRQ);
            }
            
                
            sprintf(tmt, "status = %02X\r\n", stat);                 
            USB_UART_SpiUartPutArray(tmt, sizeof(tmt));
        }
        else //rx
        {
            uint8_t stat = nRF24_get_status();
            
            //if data is pending
            if(nRF24_is_data_ready())
            {
                LED_Write(~LED_Read());
                
                nRF24_clear_irq_flag(NRF_RX_DR_IRQ);
                    
                nRF24_get_rx_payload(rcv, 2);
                sprintf(tmt, "data = %02X, %02X \r\n", rcv[0],rcv[1]);                 
                USB_UART_SpiUartPutArray(tmt, sizeof(tmt)); CyDelay(10);                
            }
            sprintf(tmt, "status = %02X \r\n", stat);                 
            USB_UART_SpiUartPutArray(tmt, sizeof(tmt)); CyDelay(10);
                        
        }
        
          
             
    }
    
    
    for(;;)
    {
        /* Place your application code here. */
        
        //Feed the dog (512ms)
        CySysWatchdogFeed(CY_SYS_WDT_COUNTER0);                 
        
        //service modbus request if available
        modbusRTU_Update(1, modbus_holding_regs, MB_HREGS);
        
        //read current position
        pid_fb = (int)QuadDec_ReadCounter() - 0x8000;
        
        //send pid output to motor
        Motor_Bidirectional((int)motor_pwm); 
        
        //current pwm sent to motor in percentage
        modbus_holding_regs[Current_PWM] = (int)(motor_pwm/65536.0*100.0);
                   
        //send the current reading to holding register so that it can be monitored via modbus link
        modbus_holding_regs[Current_Encoder_Position] = (int)pid_fb;
        
        //fetch the latest settings from hregs
        setpoint = (float)(short)modbus_holding_regs[PID_Setpoint];       
        
        //define pid gains (take from hregs)
        PID_Set_Gains((float)modbus_holding_regs[Kp], (float)modbus_holding_regs[Ki], (float)modbus_holding_regs[Kd]);
        
        //Current measurement
        modbus_holding_regs[CurrSense_A] = ADC_GetResult16(0); 
        modbus_holding_regs[CurrSense_B] = ADC_GetResult16(1);         
        
        //Emergency Stop
        if(modbus_holding_regs[Soft_Reset] != 0)
        {
            Motor_Bidirectional(0); 
            PID_Set_Gains(0.0, 0.0, 0.0);
            CySoftwareReset();
        }
            
    }
}

/* [] END OF FILE */
