/*
 * buffered_serial_B.h
 *
 *  Created on: 17 March 2018
 *      Author: AfdhalAtiffTan
 *      Based on Arduino SoftSerial Library.
 */

#ifndef BUFFERED_SERIAL_B_H_
#define BUFFERED_SERIAL_B_H_

#include "includes.h"

void buffered_serial_B_write(char c);
char buffered_serial_B_read();
char buffered_serial_B_available();
void buffered_serial_B_flush();

//for ISRs
void buffered_serial_B_receive();
void buffered_serial_B_transmit();


extern volatile char eusartTxBufferRemaining_B;

#endif /* BUFFERED_SERIAL_H_ */
