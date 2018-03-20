/*
 * motion_buffer.h
 *
 *  Created on: 16 Mar 2018
 *      Author: AfdhalAtiffTan
 */

#ifndef MOTION_BUFFER_H_
#define MOTION_BUFFER_H_

#include "includes.h"

void motion_buffer_init();
void motion_buffer_push(uint16_t i);
uint16_t motion_buffer_pop();
bool motion_buffer_isEmpty();
bool motion_buffer_isFull();

#endif /* MOTION_BUFFER_H_ */
