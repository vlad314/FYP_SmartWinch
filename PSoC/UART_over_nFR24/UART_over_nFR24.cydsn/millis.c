/*
 * File:   millis.c
 * Author: Afdhal Tan
 *
 * Created on 21 October 2016, 13:32
 */

#include "millis.h"
volatile unsigned long long long_millis=0;

CY_ISR(Millis_Tick)
{
    long_millis+=1;

//    //for debug use    
//    static int cnt=0;
//     
//    //heartbeat on led
//    if(cnt++>100)
//    {
//        cnt=0;
//        LED_Write(~LED_Read());
//    } 
    
    //clear flags before exiting isr
    Millis_TMR_ClearInterrupt(Millis_TMR_INTR_MASK_TC);
    Millis_ISR_ClearPending();
}

void Millis_Start()
{
    Millis_ISR_StartEx(Millis_Tick);
    Millis_TMR_Start();
}

/* [] END OF FILE */
