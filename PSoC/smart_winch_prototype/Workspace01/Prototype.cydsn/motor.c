/*******************************************************************************
* File Name: motor.c  
* Version 0.1
* 6th November 2017
*
*  Description:
*   APIs for motor controller.
********************************************************************************
 * Copyright AfdhalAtiffTan, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
*******************************************************************************/

#include "motor.h"

/*******************************************************************************
* Function Name: Motor_Bidirectional
********************************************************************************
*
* Summary:
*  -Control the speed and the direction of the motor.
*  -It accepts 0 to 65535 as the duty cycle.
*  -Positive and negative value correspond to forward and backward respectively.
*
* Parameters:  
*   *pwm: Set the speed and the direction of the motor by giving it +/- 0 to 65535 
*
* Return:
*   None
*
*******************************************************************************/
void Motor_Bidirectional(int pwm)
{
    //boundaries check
    if (pwm>65535)
        pwm = 65535;
    else if (pwm<-65535)
        pwm = -65535;
    
    //set direction first
    if (pwm<0) //reverse
    {    
        Motor_Dir_Write(1);
        pwm *= -1; //take only the magnitude
    }
    else //forward
    {
        Motor_Dir_Write(0);
    }
            
    //then, set duty cycle
    PWM_WriteCompare(pwm);    
}


/*******************************************************************************
* Function Name: Motor_Start
********************************************************************************
*
* Summary:
*  Initiates the required module for motor control
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Motor_Start()
{
    Motor_Dir_Write(0); //default to forward
    PWM_WriteCompare(0); //0% duty cycle (maximum is 65535)
    PWM_Start(); //pwm for winch motor 
}

/* [] END OF FILE */
