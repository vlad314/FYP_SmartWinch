//#############################################################################
//
// FILE:   main.c
//
// TITLE:  Smart_Winch
//
// A firmware for all smart winches for eAgri Project.
//
//#############################################################################
// $TI Release: F2837xS Support Library v3.03.00.00 $
// $Release Date: Thu Dec  7 18:53:06 CST 2017 $
// $Copyright:
// Copyright (C) 2014-2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################


//
// Included Files
//
#include "includes.h"

//
// Globals
//
//temporary globals
char *msg; //for fixed const msg
char str[128]; //for runtime msg
uint16_t receivedChar[32]; //for general purpose reception


//
// Main
//
void main(void)
{
    //init required modules
    init_smartwinch();

    //
    // Send starting message.
    //
    msg = "Heeyaa\n\r";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 8);

    //give some time for power supply to settle before powering the motor (1 sec)
    DEVICE_DELAY_US(1000000);

    pid1.Kp = 40000.0f;
    pid1.Ki = 0.0f;
    pid1.Kd = 80000.0f;
    pid1.Umax = 8000000.0f;
    pid1.Umin = -8000000.0f;


    while(1)
    {
        //if a full 32-pulse was received (i.e. one full motor revolution has happened)
        if((EQEP_getStatus(EQEP1_BASE) & EQEP_STS_UNIT_POS_EVNT) != 0)
        {
            //
            // No capture overflow, i.e. if 2 consecutive revolutions happened within 10ms
            //
            if((EQEP_getStatus(EQEP1_BASE) & EQEP_STS_CAP_OVRFLW_ERROR) == 0)
            {
                float rpm = (DEVICE_SYSCLK_FREQ / 128.0) / 2.0 / EQEP_getCapturePeriodLatch(EQEP1_BASE) / 4; // 60 seconds / 120 gearbox_ratio = 2

                int len = sprintf(str, "cnt: %lu, rpm: %lu\n\r", EQEP_getPosition(EQEP1_BASE), (uint32_t) rpm);
                SCI_writeCharArray(SCIA_BASE, (uint16_t*)str, len);
            }

            //
            // Clear unit position event flag and overflow error flag
            //
            EQEP_clearStatus(EQEP1_BASE, (EQEP_STS_UNIT_POS_EVNT |
                                          EQEP_STS_CAP_OVRFLW_ERROR));
        }
    }
}

//
// End of File
//
