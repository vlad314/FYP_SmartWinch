/*
 * buffered_serial_C.h
 *
 *  Created on: 27 March 2018
 *      Author: AfdhalAtiffTan
 *      Based on Arduino SoftSerial Library.
 */

#ifndef BUFFERED_SERIAL_C_H_
#define BUFFERED_SERIAL_C_H_

#include "includes.h"

void buffered_serial_C_write(char c);
char buffered_serial_C_read();
char buffered_serial_C_available();
void buffered_serial_C_flush();

//for ISRs
void buffered_serial_C_receive();
void buffered_serial_C_transmit();


extern volatile char eusartTxBufferRemaining_C;

#endif /* BUFFERED_SERIAL_H_ */
