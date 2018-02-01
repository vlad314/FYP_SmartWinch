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

uint8_t station_id = 0;
const uint8_t A2M[] = {':', ')', 'A', '2', 'M'};
const uint8_t M2A[] = {':', ')', 'M', '2', 'A'};
const uint8_t A2B[] = {':', ')', 'A', '2', 'B'};
const uint8_t B2A[] = {':', ')', 'B', '2', 'A'};



extern volatile nrf_irq nRF24_Adapter_Flags;

void handle_rf();

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Write(0); //on board led off
    
    //read device id
    station_id = ID_Read();
    
    //init nRF24L01 module
    nRF24_Adapter_Start();    
    nRF24_set_mode(NRF_MODE_RX);
    nRF24_set_rx_mode();
    nRF24_set_channel(120);    
    
    switch (station_id)
    {
        //master, node 0, A
        case 0:
        {
            nRF24_set_tx_address(A2B, 5);
            nRF24_set_rx_pipe_0_address(M2A, 5);
            //nRF24_set_rx_pipe_1_address(B2A, 5);
            break;
        }
        
        //slave, node 1, B
        case 1:
        {
            nRF24_set_tx_address(B2A, 5);
            nRF24_set_rx_pipe_0_address(A2B, 5);
            break;
        }
        default:
        {
            //error condition, should never reach here
            while(1)
            {
                LED_Write(~LED_Read());
                CyDelay(50);                
            }
        }
    }
    
    nRF24_start_listening();
    
    
    
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
    PID_Set_Output_Limits(-65536*.5, 65536*.5); //pwm resolution reduced to 15-bits due to acoustic noise
    
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
               
           
    for(;;)
    {        
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
            if(station_id==0)
            {
                static uint8_t dataToSend[4];
                nRF24_set_tx_mode();            
                
                dataToSend[0] = Soft_Reset;
                dataToSend[1] = modbus_holding_regs[Soft_Reset]>>8; //msb
                dataToSend[2] = modbus_holding_regs[Soft_Reset]&0xff; //lsb
                dataToSend[3] = 0;
                
                nRF24_transmit(dataToSend, 4); 
                CyDelay(10);
                nRF24_transmit(dataToSend, 4); 
                CyDelay(10);
                nRF24_transmit(dataToSend, 4); 
                CyDelay(10);
                nRF24_transmit(dataToSend, 4); 
                CyDelay(10);
                nRF24_transmit(dataToSend, 4); 
                CyDelay(10);
            }
                                    
            Motor_Bidirectional(0); 
            PID_Set_Gains(0.0, 0.0, 0.0);   
            QuadDec_WriteCounter(0x8000); //reset measure cable distance (it resets to 32768)
            CySoftwareReset();
        }                
        
        handle_rf();
    }
}

void handle_rf()
{
    //buffers
    static uint8_t rcv0[16];
    static uint8_t rcv1[16];
    static uint8_t dataToSend[16];
    
    //reception flag
    static uint8_t updated_input = 0;
    
    if(station_id == 0)
    {                
        if(modbusRTU_Written == 1)
        {    
            nRF24_stop_listening();
            nRF24_set_tx_mode();            
            
            if((modbusRTU_written_register_flags)&(1<<Kp))
            {
                dataToSend[0] = Kp;
                dataToSend[1] = modbus_holding_regs[Kp]>>8; //msb
                dataToSend[2] = modbus_holding_regs[Kp]&0xff; //lsb
                dataToSend[3] = 0;
                modbusRTU_written_register_flags &= ~(1<<Kp);
                
            }
            else if((modbusRTU_written_register_flags)&(1<<Ki))
            {
                dataToSend[0] = Ki;
                dataToSend[1] = modbus_holding_regs[Ki]>>8; //msb
                dataToSend[2] = modbus_holding_regs[Ki]&0xff; //lsb
                dataToSend[3] = 0;
                modbusRTU_written_register_flags &= ~(1<<Ki);
            }
            else if((modbusRTU_written_register_flags)&(1<<Kd))
            {
                dataToSend[0] = Kd;
                dataToSend[1] = modbus_holding_regs[Kd]>>8; //msb
                dataToSend[2] = modbus_holding_regs[Kd]&0xff; //lsb
                dataToSend[3] = 0;
                modbusRTU_written_register_flags &= ~(1<<Kd);
            }
            else if((modbusRTU_written_register_flags)&(1<<PID_Setpoint1))
            {
                dataToSend[0] = PID_Setpoint;
                dataToSend[1] = modbus_holding_regs[PID_Setpoint1]>>8; //msb
                dataToSend[2] = modbus_holding_regs[PID_Setpoint1]&0xff; //lsb
                dataToSend[3] = 0;
                modbusRTU_written_register_flags &= ~(1<<PID_Setpoint1);
            }
            
            else if((modbusRTU_written_register_flags)&(1<<Soft_Reset))
            {
                dataToSend[0] = Soft_Reset;
                dataToSend[1] = modbus_holding_regs[Soft_Reset]>>8; //msb
                dataToSend[2] = modbus_holding_regs[Soft_Reset]&0xff; //lsb
                dataToSend[3] = 0;
                modbusRTU_written_register_flags &= ~(1<<Soft_Reset);
            }
                        
            nRF24_transmit(dataToSend, 4); 
            CyDelay(10);
            nRF24_transmit(dataToSend, 4); 
            CyDelay(10);
            nRF24_transmit(dataToSend, 4); 
            CyDelay(10);
            nRF24_transmit(dataToSend, 4); 
            CyDelay(10);
            nRF24_transmit(dataToSend, 4); 
            CyDelay(10);
            
            
            nRF24_clear_all_irqs();
            LED_Write(~LED_Read());
            
//            if (!nRF24_is_tx_fifo_full())
//            {
//                nRF24_transmit(dataToSend, 4); 
//            }
//            else //retransmitting packet
//            {
//                nRF24_reuse_last_transmitted_payload();
//                nRF24_clear_irq_flag(NRF_MAX_RT_IRQ); //acknowledge failed retransmission
//            }
//                
//            //if transmit sucessful
//            if(NRF_STATUS_TX_DS_MASK & nRF24_get_status())
//            {
//                LED_Write(~LED_Read());
//                
//                nRF24_set_rx_mode();
//                nRF24_start_listening();
//                
//                nRF24_clear_irq_flag(NRF_TX_DS_IRQ);
//            }  
            
            //clear flag when all changes acknowledged            
            if((modbusRTU_written_register_flags&0x00000407) == 0)
                modbusRTU_Written = 0;    
        }   
        else
        {
            nRF24_set_rx_mode();
            //nRF24_set_mode(NRF_MODE_RX);
            
            nRF24_start_listening();
        }
    }
    
    
    //future: use interrupt
    if(nRF24_is_data_ready())
    {
        LED_Write(~LED_Read());        
        nRF24_clear_irq_flag(NRF_RX_DR_IRQ);
        
        uint8_t full_rx_fifo_address = nRF24_get_data_pipe_with_payload();
        
        while(full_rx_fifo_address != 7)
        {
            switch(full_rx_fifo_address)
            {
                case 0:
                {
                    nRF24_get_rx_payload(rcv0, 4);
                    updated_input |= 1 << 0;
                    break;
                }
                case 1:
                {
                    nRF24_get_rx_payload(rcv1, 4);
                    updated_input |= 1 << 1;
                    break;
                }
            }
            
            full_rx_fifo_address = nRF24_get_data_pipe_with_payload();
        }
        
        //Node A
        if (station_id == 0)
        {
            if(updated_input&(1<<0))
            {                                
                switch(rcv0[0])
                {
                    case Kp:
                    {
                        modbus_holding_regs[Kp] = (rcv0[1]<<8) | rcv0[2];
                        modbusRTU_Written |= 1;
                        modbusRTU_written_register_flags |= (1<<Kp);                        
                        break;
                    }
                    case Ki:
                    {
                        modbus_holding_regs[Ki] = (rcv0[1]<<8) | rcv0[2];
                        modbusRTU_Written |= 1;
                        modbusRTU_written_register_flags |= (1<<Ki);
                        break;
                    }
                    case Kd:
                    {
                        modbus_holding_regs[Kd] = (rcv0[1]<<8) | rcv0[2];
                        modbusRTU_Written |= 1;
                        modbusRTU_written_register_flags |= (1<<Kd);
                        break;
                    }
                    case PID_Setpoint:
                    {
                        modbus_holding_regs[PID_Setpoint] = (rcv0[1]<<8) | rcv0[2];                        
                        break;
                    }
                    case PID_Setpoint1:
                    {
                        modbus_holding_regs[PID_Setpoint1] = (rcv0[1]<<8) | rcv0[2];
                        modbusRTU_Written |= 1;
                        modbusRTU_written_register_flags |= (1<<PID_Setpoint1);
                        break;
                    }
                    case Soft_Reset:
                    {
                        modbus_holding_regs[Soft_Reset] = (rcv0[1]<<8) | rcv0[2];
                        modbusRTU_Written |= 1;
                        modbusRTU_written_register_flags |= (1<<Soft_Reset);
                        break;
                    }
                }
                //clear flag
                updated_input &= ~(1<<0);
            }
        }
        
        //Node B
        if (station_id == 1)
        {
            if(updated_input&(1<<0))
            {                                
                switch(rcv0[0])
                {
                    case Kp:
                    {
                        modbus_holding_regs[Kp] = (rcv0[1]<<8) | rcv0[2];
                        break;
                    }
                    case Ki:
                    {
                        modbus_holding_regs[Ki] = (rcv0[1]<<8) | rcv0[2];
                        break;
                    }
                    case Kd:
                    {
                        modbus_holding_regs[Kd] = (rcv0[1]<<8) | rcv0[2];
                        break;
                    }
                    case PID_Setpoint:
                    {
                        modbus_holding_regs[PID_Setpoint] = (rcv0[1]<<8) | rcv0[2];
                        break;
                    }
                    case Soft_Reset:
                    {
                        modbus_holding_regs[Soft_Reset] = (rcv0[1]<<8) | rcv0[2];
                        break;
                    }
                }
                //clear flag
                updated_input &= ~(1<<0);
            }
        }                                        
    }
}

/* [] END OF FILE */
