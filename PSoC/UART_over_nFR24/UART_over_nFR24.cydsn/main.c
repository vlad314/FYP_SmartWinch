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
#include "project.h"
#include "millis.h"
#include "ring_buffer.h"

//#define DEBUG_MODE
#define INTERCHAR_TIMEOUT 10 //ms 

//Pipes to be used for nRF24 modules
const uint8_t M2S[] = {':', ')', 'M', '2', 'S'}; //master to slave
const uint8_t S2M[] = {':', ')', 'S', '2', 'M'}; //slave to master

uint8_t nrf24_TX_buf[32];
uint8_t nrf24_RX_buf[256];

uint8_t number_of_char_received_uart = 0;
uint8_t number_of_char_received_usb = 0;
uint8_t number_of_char_received_nRF = 0;

bool done_receiving_from_uart_flag = 0;
bool done_receiving_from_usb_flag = 0;
bool done_receiving_from_nRF_flag = 0;


#define NRF_CMD_ACTIVATE 0x50
void nRF24_activate_cmd()
{
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_CMD_ACTIVATE);
    SPI_SpiUartWriteTxData(0x73); //see datasheet

    while (SPI_SpiUartGetRxBufferSize() != 2);    
    SS_Write(1);
}

uint8_t nRF24_read_rx_payload_width_cmd()
{
    uint8_t data;
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_CMD_R_RX_PL_WID);
    SPI_SpiUartWriteTxData(NRF_CMD_NOP);
    while (SPI_SpiUartGetRxBufferSize() != 2);
    
    // Read the status register, just to clear the rx fifo
    SPI_SpiUartReadRxData();
    
    //the actual data
    data = SPI_SpiUartReadRxData();
    
    SS_Write(1);
    
    return data;
}

void MyInst_Start()
{
    Millis_Start();
    USB_UART_Start();
    UART_Start();
    nRF24_start();  
           
    nRF24_enable_dynamic_payload_length();  
    
    nRF24_activate_cmd();
    
    nRF24_set_rx_mode();
    nRF24_set_channel(120); 
    
    if(MASTER_UNIT_Read() == 0)
    {
        nRF24_set_tx_address(M2S, 5);
        nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, S2M, 5);
    }
    else
    {
        nRF24_set_tx_address(S2M, 5);
        nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, M2S, 5);
    }                 
    
    nRF24_start_listening();
    nRF24_flush_rx();
    nRF24_flush_tx();
    ring_buffer_init();
}

void transparent_bridge()
{
    while(USB_UART_SpiUartGetRxBufferSize())
        UART_SpiUartWriteTxData(USB_UART_SpiUartReadRxData());
    while(UART_SpiUartGetRxBufferSize())
        USB_UART_SpiUartWriteTxData(UART_SpiUartReadRxData());    
}

//will return 1 if new packet frame came in
uint32_t usb_uart_new_frame()
{
    uint32_t now = millis();
    uint32_t length = USB_UART_SpiUartGetRxBufferSize();
    static uint32_t Nowdt = 0;
    static uint32_t lastBytesReceived = 0;
    
    //check if there is any activity on usb_uart
    if (length == 0) 
    {
        lastBytesReceived = 0;
        return 0;
    }
    
    //if data is still streaming in
    if (lastBytesReceived != length)
    {
        Nowdt = now + INTERCHAR_TIMEOUT;
        lastBytesReceived = length;
        return 0;
    }

    //check to see if interchar_timout has occured
    if (now < Nowdt)
        return 0;

    lastBytesReceived = 0;    
    
    return 1;
}


//will return 1 if new packet frame came in
uint32_t uart_new_frame()
{
    uint32_t now = millis();
    uint32_t length = UART_SpiUartGetRxBufferSize();
    static uint32_t Nowdt = 0;
    static uint32_t lastBytesReceived = 0;
    
    //check if there is any activity on usb_uart
    if (length == 0) 
    {
        lastBytesReceived = 0;
        return 0;
    }
    
    //if data is still streaming in
    if (lastBytesReceived != length)
    {
        Nowdt = now + INTERCHAR_TIMEOUT;
        lastBytesReceived = length;
        return 0;
    }

    //check to see if interchar_timout has occured
    if (now < Nowdt)
        return 0;

    lastBytesReceived = 0;    
    
    return 1;
}


//will return 1 if new packet frame came in
uint32_t nrf_new_frame()
{
    if(NRF_ISR_Read() == 0 && nRF24_is_data_ready())
    {
        LED_Write(~LED_Read());
        uint16_t count = nRF24_read_rx_payload_width_cmd();
        nRF24_get_rx_payload(nrf24_RX_buf, count);
        nRF24_clear_all_irqs();
        
        nRF24_flush_rx();
        
        uint16_t i=0;
        for(i=0; i<count;i++)
        {
            ring_buffer_push((uint16_t)nrf24_RX_buf[i]);
        }
    }
    
    uint32_t now = millis();
    uint32_t length =  ring_buffer_available();
    static uint32_t Nowdt = 0;
    static uint32_t lastBytesReceived = 0;        
    
    //check if there is any activity on nrf
    if (length == 0) 
    {
        lastBytesReceived = 0;
        return 0;
    }
    
    //if data is still streaming in
    if (lastBytesReceived != length)
    {
        Nowdt = now + INTERCHAR_TIMEOUT;
        lastBytesReceived = length;
        return 0;
    }

    //check to see if interchar_timout has occured
    if (now < Nowdt)
        return 0;

    lastBytesReceived = 0;            
    return 1;
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    MyInst_Start();    
    
    for(;;)
    {
        /* Place your application code here. */        
        //transparent_bridge(); //debug            
        
        if(nrf_new_frame())
            done_receiving_from_nRF_flag = 1;
        
        if(usb_uart_new_frame())
            done_receiving_from_usb_flag = 1;
        
        if(uart_new_frame())
            done_receiving_from_uart_flag = 1;
                              
        if(done_receiving_from_nRF_flag)
        {
            done_receiving_from_nRF_flag = 0;
            
            //transfer from ring buffer to 256buf            
            number_of_char_received_nRF = ring_buffer_available();
            uint16_t i=0;
            
            for(i=0;i<number_of_char_received_nRF;i++)
            {
                nrf24_RX_buf[i] = ring_buffer_pop();
            }
            
            ring_buffer_flush();
            
            if(MASTER_UNIT_Read() == 0)
                USB_UART_SpiUartPutArray(nrf24_RX_buf, number_of_char_received_nRF);
            else
                UART_SpiUartPutArray(nrf24_RX_buf, number_of_char_received_nRF);              
        }
        
        if(done_receiving_from_usb_flag)
        {            
            done_receiving_from_usb_flag = 0;
                        
            nRF24_stop_listening();
            nRF24_set_tx_mode(); 
            
            CyDelay(3);
            
            number_of_char_received_usb = USB_UART_SpiUartGetRxBufferSize(); //maybe useless
            
            nRF24_flush_tx();
            
            //logic here is to split the 256fifo into chunks for 32fifo
            uint16_t chunk_size = 0;            
            while(USB_UART_SpiUartGetRxBufferSize()) //while data is pending to be radio transmited
            {
                //give it some time before sending the next chunk
                //CyDelay(1);
                
                //split it into 32B chunks
                if(USB_UART_SpiUartGetRxBufferSize() >= 32)
                    chunk_size = 32;
                else
                    chunk_size = USB_UART_SpiUartGetRxBufferSize();
                    
                //put it into nrf tx buffer    
                uint32_t i = 0;                
                for(i = 0; i < chunk_size; i++)
                {
                    nrf24_TX_buf[i] = USB_UART_SpiUartReadRxData();                    
                }
                
                //push it to air    
                nRF24_tx_transmit_no_ack(nrf24_TX_buf, chunk_size); 
                while(NRF_ISR_Read());
                nRF24_flush_tx();
                nRF24_clear_all_irqs(); //ignore any dropped packet   
            }
                                                                        
            nRF24_set_rx_mode();
            nRF24_start_listening();
                    
        }      
        
        if(done_receiving_from_uart_flag)
        {            
            done_receiving_from_uart_flag = 0;
                        
            nRF24_stop_listening();
            nRF24_set_tx_mode(); 
            
            CyDelay(3);
            
            number_of_char_received_uart = UART_SpiUartGetRxBufferSize(); //maybe useless
            
            nRF24_flush_tx();
            
            //logic here is to split the 256fifo into chunks for 32fifo
            uint16_t chunk_size = 0;            
            while(UART_SpiUartGetRxBufferSize()) //while data is pending to be radio transmited
            {
                //give it some time before sending the next chunk
                //CyDelay(1);
                
                //split it into 32B chunks
                if(UART_SpiUartGetRxBufferSize() >= 32)
                    chunk_size = 32;
                else
                    chunk_size = UART_SpiUartGetRxBufferSize();
                    
                //put it into nrf tx buffer    
                uint32_t i = 0;                
                for(i = 0; i < chunk_size; i++)
                {
                    nrf24_TX_buf[i] = UART_SpiUartReadRxData();                    
                }
                
                //push it to air    
                nRF24_tx_transmit_no_ack(nrf24_TX_buf, chunk_size); 
                while(NRF_ISR_Read());
                nRF24_flush_tx();
                nRF24_clear_all_irqs(); //ignore any dropped packet   
            }
                                                                        
            nRF24_set_rx_mode();
            nRF24_start_listening();                    
        }  
    }
}

/* [] END OF FILE */
