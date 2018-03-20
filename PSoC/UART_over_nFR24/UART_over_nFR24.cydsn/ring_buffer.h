/*
 * ring_buffer.h
 *
 *  Created on: 16 Mar 2018
 *      Author: AfdhalAtiffTan
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "project.h"
#include "stdlib.h"
    
void ring_buffer_init();
void ring_buffer_push(uint16_t i);
uint16_t ring_buffer_pop();
bool ring_buffer_isEmpty();
bool ring_buffer_isFull();
uint16_t ring_buffer_available();
void ring_buffer_flush();

#endif /* MOTION_BUFFER_H_ */
