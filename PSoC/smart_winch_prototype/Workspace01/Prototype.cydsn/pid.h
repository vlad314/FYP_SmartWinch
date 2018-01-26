/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"

void PID_Set_Gains(float _kp, float _ki, float _kd);
void PID_Init();
void PID_Set_Setpoint(float *_setpoint);
void PID_Set_Input(float *_input);
void PID_Set_Output(float *_output);
void PID_Set_Output_Limits(float _out_min, float _out_max);
CY_ISR_PROTO(PID_Tick);


/* [] END OF FILE */
