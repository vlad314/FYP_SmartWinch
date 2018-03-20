/*
 * buffered_serial_B.c
 *
 *  Created on: 17 March 2018
 *      Author: AfdhalAtiffTan
 */


#include "buffered_serial_B.h"

// static data
#define EUSART_TX_BUFFER_SIZE 0xFF
static char eusartTxHead = 0;
static char eusartTxTail = 0;
static char eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
volatile char eusartTxBufferRemaining_B=EUSART_TX_BUFFER_SIZE;
volatile char TXIE_B = 0;

#define MAX_BUFF 0xFF
static char _receive_buffer[MAX_BUFF];
static volatile char _receive_buffer_tail=0;
static volatile char _receive_buffer_head=0;


//ported from microchip mcc usart driver
void buffered_serial_B_write(char c)
{
    while(0 == eusartTxBufferRemaining_B)
    {
    }


    if(0 == TXIE_B)
    {
        //TX1REG = txData;
        SCI_writeCharBlockingFIFO(SCIB_BASE, c);
    }
    else
    {
        TXIE_B = 0;
        Interrupt_disable(INT_SCIB_TX);

        eusartTxBuffer[eusartTxHead++] = c;
        if(EUSART_TX_BUFFER_SIZE <= eusartTxHead)
        {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining_B--;
    }

    //only set isr when tx fifo is full
    if(SCI_getTxFIFOStatus(SCIB_BASE) < SCI_FIFO_TX16) //this might not work properly
    {
        TXIE_B = 1;
        Interrupt_enable(INT_SCIB_TX);
    }
}

//ported from arduino softserial library
char buffered_serial_B_read()
{
    // Empty buffer?
    if (_receive_buffer_head == _receive_buffer_tail)
      return -1;

    // Read from "head"
    char d = _receive_buffer[_receive_buffer_head]; // grab next byte
    _receive_buffer_head = (_receive_buffer_head + 1) % MAX_BUFF;
    return d;
}

//ported from arduino softserial library
char buffered_serial_B_available()
{
    return (_receive_buffer_tail + MAX_BUFF - _receive_buffer_head) % MAX_BUFF;
}

//ported from arduino softserial library
void buffered_serial_B_receive()
{
    // if buffer full, set the overflow flag and return
    char next = (_receive_buffer_tail + 1) % MAX_BUFF;
    if (next != _receive_buffer_head)
    {
      // save new data in buffer: tail points to where byte goes
      _receive_buffer[_receive_buffer_tail] = SCI_readCharNonBlocking(SCIB_BASE); // save new byte
      _receive_buffer_tail = next;
    }

}

//ported from microchip mcc usart driver
void buffered_serial_B_transmit()
{
    // add your EUSART interrupt custom code
    if(EUSART_TX_BUFFER_SIZE > eusartTxBufferRemaining_B)
    {
        //TX1REG = eusartTxBuffer[eusartTxTail++];

        //fillup fifo
        while((EUSART_TX_BUFFER_SIZE > eusartTxBufferRemaining_B) && (SCI_getTxFIFOStatus(SCIB_BASE) < SCI_FIFO_TX16)) //this might not work properly
        {
            SCI_writeCharBlockingFIFO(SCIB_BASE, eusartTxBuffer[eusartTxTail++]);
            if(EUSART_TX_BUFFER_SIZE <= eusartTxTail)
            {
                eusartTxTail = 0;
            }
            eusartTxBufferRemaining_B++;
        }
    }
    else
    {
        TXIE_B = 0;
        Interrupt_disable(INT_SCIB_TX);
    }

    //GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
}
