/*
 * File:   nRF24_Adapter.c
 * Author: Afdhal Tan
 *
 * Created on 17 December 2017, 22:32
 *
 * This file is meant to interface the C47F's nRF24 library (including ISR)
 */

#ifndef nRF24_Adapter_H
#define nRF24_Adapter_H

#include "project.h"
    
volatile nrf_irq nRF24_Adapter_Flags;
 
CY_ISR_PROTO(nRF24_ISR);    
void nRF24_Adapter_Start();
    
#endif

/* [] END OF FILE */