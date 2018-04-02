//#############################################################################
//
// FILE:   main.c
//
// TITLE:  SmartWinchDualCore
//
// MEng Final Year Project
//
// This project was prepared by importing the single-core driverlib empty project.
//
//#############################################################################
// $TI Release: F2837xD Support Library v3.03.00.00 $
// $Release Date: Thu Dec  7 18:51:32 CST 2017 $
// $Copyright:
// Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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


//todo: save this in eeprom
void init_settings()
{
    modbus_holding_regs[Kp] = 4096;
    modbus_holding_regs[Ki] = 0;
    modbus_holding_regs[Kd] = 30000;

    pid1.Umax = 16777215.0f;
    pid1.Umin = -16777215.0f;

    modbus_holding_regs[Field_Length] = 1000;
    modbus_holding_regs[Field_Width] = 1000;

    //default motion settings - 19th feb 2018
    modbus_holding_regs[Max_Velocity] = 50; /* mm/s */
    modbus_holding_regs[Max_Acceleration] = 50; /* mm/s^2 */

    //30th march 2018
    modbus_holding_regs[Kp_velocity] = 16;
    modbus_holding_regs[Ki_velocity] = 0;
    modbus_holding_regs[Kd_velocity] = 0;
    modbus_holding_regs[Max_Encoder_Feedrate] = 250; /* no load max speed in mm/s */

    modbus_holding_regs[Kp_position] = 2048;
    modbus_holding_regs[Ki_position] = 0;
    modbus_holding_regs[Kd_position] = 0;    
}

//
// Main
//
void main(void)
{
    init_settings();

    //init required modules
    init_smartwinch();

    //read WinchId on dip-switches - added on 18th feb 2018
    modbus_holding_regs[Winch_ID] = 0x03^((GPIO_readPin(DEVICE_GPIO_PIN_ID0)<<1) | (GPIO_readPin(DEVICE_GPIO_PIN_ID1))); //active-low switches

    //MotionProfile((float) modbus_holding_regs[Max_Velocity], (float) modbus_holding_regs[Max_Acceleration], 1, 0);

    // Send starting message. todo: send help messages instead
    msg = "Heeyaa\n\r";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 8);    

    //main loop
    while(1)
    {
        //service modbus request if available
        modbusRTU_Update((modbus_holding_regs[Winch_ID]+1), modbus_holding_regs, MB_HREGS);

        //force system reset
       if(modbus_holding_regs[Soft_Reset] != 0)
       {
           modbus_holding_regs[Soft_Reset] = 0;
           SysCtl_resetDevice();
       }

        //switch status
        modbus_holding_regs[Winch_ID] = 0x03^((GPIO_readPin(DEVICE_GPIO_PIN_ID0)<<1) | (GPIO_readPin(DEVICE_GPIO_PIN_ID1))); //active-low switches

        //debugging mode, if enabled, the modbus will be on uart_usb instead of on uart_wireless
        DEBUGGING = GPIO_readPin(DEVICE_GPIO_PIN_DBG);

        task_scheduler_handler(); // main program  

        static uint32_t loop_counter = 0;
        if(loop_counter == 0)
            GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
        loop_counter+=1;   
        loop_counter&=0x0f;    
    }
}

//
// End of File
//


/*
        //update per second
        static uint32_t prev_systick = 0;
        if(systick() - prev_systick > 500)
        {
            prev_systick = systick();            
            GPIO_togglePin(DEVICE_GPIO_PIN_LED1);           
        }   
*/

        // //update per second
        // static uint32_t prev_systick = 0;
        // if(systick() - prev_systick > 5000)
        // {
        //     prev_systick = systick();
            
        //     // //motion control
        //     // MotionProfile_setMaxVelocity((float) modbus_holding_regs[Max_Velocity]);
        //     // MotionProfile_setMaxAcceleration((float) modbus_holding_regs[Max_Acceleration]);            
        // }  
