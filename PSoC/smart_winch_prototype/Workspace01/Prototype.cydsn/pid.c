/*******************************************************************************
* File Name: pid.c  
* Version 0.1
* 16th October 2017
*
*  Description:
*   APIs for PID controller.
*
*
*  Note:  
*   Future: 
*       -Implement decay variable for integral.
*       -Implement filter for PD.
********************************************************************************
 * Copyright AfdhalAtiffTan, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
*******************************************************************************/

#include "pid.h"

//gain for p, i, and d.
static float kp,ki,kd;

//setpoint is the desired target, input is the feedback (e.g. rotary encoder), and output is the final output (all pid summed)
static float *setpoint, *input, *output;

//errors
static float error, input_previous, error_integrated, input_differentiated;

//limits
static float out_min, out_max;


/*******************************************************************************
* Function Name: PID_Set_Gains
********************************************************************************
*
* Summary:
*  Set the gain for all components (Propotional, Integral, Derivative)
*
* Parameters:  
*   *_kp: Gain for proportional.
*   *_ki: Gain for integral.
*   *_kd: Gain for derivative.
*
* Return:
*   None
*
*******************************************************************************/
void PID_Set_Gains(float _kp, float _ki, float _kd)
{
    kp = _kp;
    ki = _ki;
    kd = _kd;
}


/*******************************************************************************
* Function Name: PID_Init
********************************************************************************
*
* Summary:
*  Initialised all cumulated variables to zero and initialise variables.
*
* Parameters:  
*   None.
*
* Return:
*   None
*
*******************************************************************************/
void PID_Init()
{
    kp = 1.0;
    ki = 0.0;
    kd = 0.0;
    
    input_previous = 0.0;
    error_integrated = 0.0;
    
    out_min = -65535.0;
    out_max = 65535.0;
}


/*******************************************************************************
* Function Name: PID_Set_Setpoint
********************************************************************************
*
* Summary:
*  Set the location of "setpoint" variable (e.g. desired position)
*
* Parameters:  
*   *_setpoint: The address of an "setpoint" variable (must use & operator)
*
* Return:
*   None
*
*******************************************************************************/
void PID_Set_Setpoint(float *_setpoint)
{
    setpoint = _setpoint;
}


/*******************************************************************************
* Function Name: PID_Set_Input
********************************************************************************
*
* Summary:
*  Set the location of "feedback" variable (e.g. reading from rotary decoder)
*
* Parameters:  
*   *_input: The address of a "feedback" variable (must use & operator)
*
* Return:
*   None
*
*******************************************************************************/
void PID_Set_Input(float *_input)
{
    input = _input;
}


/*******************************************************************************
* Function Name: PID_Set_Output
********************************************************************************
*
* Summary:
*  Set the location of "output" variable (e.g. output to pwm)
*
* Parameters:  
*   *_output: The address of an "output" variable (must use & operator)
*
* Return:
*   None
*
*******************************************************************************/
void PID_Set_Output(float *_output)
{
    output = _output;
}


/*******************************************************************************
* Function Name: PID_Set_Output_Limits
********************************************************************************
*
* Summary:
*  Set the upper and lower limit for the output so that windup can be avoided.
*
* Parameters:  
*   _out_min: The lowest number that the output is allowed.
*   _out_max: The highest number that the output is allowed.
*
* Return:
*   None
*
*******************************************************************************/
void PID_Set_Output_Limits(float _out_min, float _out_max)
{
    out_min = _out_min;
    out_max = _out_max;
}


/*******************************************************************************
* Function Name: PID_Tick
********************************************************************************
*
* Summary:
*   This function should be called periodically (e.g. 100Hz) during runtime.
*   It handles PID maths and its output.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(PID_Tick)
{
//    static int cnt=0;
     
//    //heartbeat on led
//    if(cnt++>15)
//    {
//        cnt=0;
//        LED_Write(~LED_Read());
//    }        
     
    //<Proportional>
    error = *setpoint - *input;    
    *output = kp*error;
    //</Proportional>
    
    //<Integration>
    error_integrated += error;
        
    //preventing integrator windup   
    error_integrated = error_integrated > out_max ? out_max : error_integrated;
    error_integrated = error_integrated < out_min ? out_min : error_integrated;
    
    //reseting integrator
    if(ki == 0.0)
        error_integrated = 0.0;
    
    *output += ki/1000.0*error_integrated; //added divide by 1000 to allow for fractional math
    //</Integration>
    
    //<Differentiation> (“Derivative on Measurement”)
    input_differentiated = *input - input_previous;    
    input_previous = *input;
    
    *output -= kd * input_differentiated;
    //</Differentiation>
    
    //output clamp
    *output = *output > out_max ? out_max : *output;
    *output = *output < out_min ? out_min : *output;
            
    PID_Tick_Timer_ClearInterrupt(PID_Tick_Timer_INTR_MASK_TC);
    PID_ISR_ClearPending();
}
/* [] END OF FILE */