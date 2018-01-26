/*******************************************************************************
* File Name: PID_Tick_Timer_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PID_Tick_Timer.h"

static PID_Tick_Timer_BACKUP_STRUCT PID_Tick_Timer_backup;


/*******************************************************************************
* Function Name: PID_Tick_Timer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PID_Tick_Timer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PID_Tick_Timer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PID_Tick_Timer_Sleep(void)
{
    if(0u != (PID_Tick_Timer_BLOCK_CONTROL_REG & PID_Tick_Timer_MASK))
    {
        PID_Tick_Timer_backup.enableState = 1u;
    }
    else
    {
        PID_Tick_Timer_backup.enableState = 0u;
    }

    PID_Tick_Timer_Stop();
    PID_Tick_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: PID_Tick_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PID_Tick_Timer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PID_Tick_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PID_Tick_Timer_Wakeup(void)
{
    PID_Tick_Timer_RestoreConfig();

    if(0u != PID_Tick_Timer_backup.enableState)
    {
        PID_Tick_Timer_Enable();
    }
}


/* [] END OF FILE */
