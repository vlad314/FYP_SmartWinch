/*
 * buffered_serial_C.c
 *
 *  Created on: 27 March 2018
 *      Author: AfdhalAtiffTan
 */


#include "buffered_serial_C.h"

// static data
#define EUSART_TX_BUFFER_SIZE_C 0xFF
static char eusartTxHead = 0;
static char eusartTxTail = 0;
static char eusartTxBuffer[EUSART_TX_BUFFER_SIZE_C];
volatile char eusartTxBufferRemaining_C=EUSART_TX_BUFFER_SIZE_C;
volatile char TXIE_C = 0;

#define MAX_BUFF_C 0xFF
static char _receive_buffer[MAX_BUFF_C];
static volatile char _receive_buffer_tail=0;
static volatile char _receive_buffer_head=0;


//ported from microchip mcc usart driver
void buffered_serial_C_write(char c)
{
    while(0 == eusartTxBufferRemaining_C)
    {
    }


    if(0 == TXIE_C)
    {
        //TX1REG = txData;
        SCI_writeCharBlockingFIFO(SCIC_BASE, c);
    }
    else
    {
        TXIE_C = 0;
        Interrupt_disable(INT_SCIC_TX);

        eusartTxBuffer[eusartTxHead++] = c;
        if(EUSART_TX_BUFFER_SIZE_C <= eusartTxHead)
        {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining_C--;
    }

    //only set isr when tx fifo is full
    if(SCI_getTxFIFOStatus(SCIC_BASE) < SCI_FIFO_TX16) //this might not work properly
    {
        TXIE_C = 1;
        Interrupt_enable(INT_SCIC_TX);
    }
}

//ported from arduino softserial library
char buffered_serial_C_read()
{
    // Empty buffer?
    if (_receive_buffer_head == _receive_buffer_tail)
      return -1;

    // Read from "head"
    char d = _receive_buffer[_receive_buffer_head]; // grab next byte
    _receive_buffer_head = (_receive_buffer_head + 1) % MAX_BUFF_C;
    return d;
}

//ported from arduino softserial library
char buffered_serial_C_available()
{
    return (_receive_buffer_tail + MAX_BUFF_C - _receive_buffer_head) % MAX_BUFF_C;
}

//flush rx buff
void buffered_serial_C_flush()
{
    _receive_buffer_head = 0;
    _receive_buffer_tail = 0;
}

//ported from arduino softserial library
void buffered_serial_C_receive()
{
    // if buffer full, set the overflow flag and return
    char next = (_receive_buffer_tail + 1) % MAX_BUFF_C;
    if (next != _receive_buffer_head)
    {
      // save new data in buffer: tail points to where byte goes
      _receive_buffer[_receive_buffer_tail] = SCI_readCharNonBlocking(SCIC_BASE); // save new byte
      _receive_buffer_tail = next;
    }

}

//ported from microchip mcc usart driver
void buffered_serial_C_transmit()
{
    // add your EUSART interrupt custom code
    if(EUSART_TX_BUFFER_SIZE_C > eusartTxBufferRemaining_C)
    {
        //TX1REG = eusartTxBuffer[eusartTxTail++];

        //fillup fifo
        while((EUSART_TX_BUFFER_SIZE_C > eusartTxBufferRemaining_C) && (SCI_getTxFIFOStatus(SCIC_BASE) < SCI_FIFO_TX16)) //this might not work properly
        {
            SCI_writeCharBlockingFIFO(SCIC_BASE, eusartTxBuffer[eusartTxTail++]);
            if(EUSART_TX_BUFFER_SIZE_C <= eusartTxTail)
            {
                eusartTxTail = 0;
            }
            eusartTxBufferRemaining_C++;
        }
    }
    else
    {
        TXIE_C = 0;
        Interrupt_disable(INT_SCIC_TX);
    }

    //GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
}
