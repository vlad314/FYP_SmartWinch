/*
 * File:   millis.c
 * Author: Afdhal Tan
 *
 * Created on 21 October 2016, 13:32
 */

#ifndef MILLIS_H
#define MILLIS_H

#include "project.h"
    
#define millis() long_millis
 
CY_ISR_PROTO(Millis_Tick);    
void Millis_Start();
    
//elapsed milliseconds - will overflow after ~50 days
volatile extern unsigned long long long_millis;
 
#endif

/* [] END OF FILE */
