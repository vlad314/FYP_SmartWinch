/*
 * task_scheduler.h
 *
 *  Created on: 17 Mar 2018
 *      Author: AfdhalAtiffTan
 */

#ifndef TASK_SCHEDULER_H_
#define TASK_SCHEDULER_H_

#include "includes.h"

extern char homing_workaround;

enum
{
    LOAD_CELL_NOT_ZEROED,
    LOAD_CELL_ZEROING_REQUEST,
    LOAD_CELL_ZEROED
};

typedef union
{
    unsigned int switch_byte;

    struct 
    {
        unsigned int BIT0 : 1;
        unsigned int BIT1 : 1;
        unsigned int BIT2 : 1;
        unsigned int BIT3 : 1;
        unsigned int BIT4 : 1;
        unsigned int BIT5 : 1;
        unsigned int BIT6 : 1;
        unsigned int BIT7 : 1;
    };

    struct 
    {
        unsigned int ADDRESS_SWITCH : 2;
        unsigned int DEBUG_SWITCH   : 1;
        unsigned int FORCE_COMP     : 1;
        unsigned int Undefined1     : 1;
        unsigned int Undefined2     : 1;
        unsigned int Undefined3     : 1;
        unsigned int Undefined4     : 1;        
    };
} DIP_switch_t;

extern DIP_switch_t dip_switch;

void task_scheduler_handler();
void read_DIP_switch();

#endif /* TASK_SCHEDULER_H_ */
