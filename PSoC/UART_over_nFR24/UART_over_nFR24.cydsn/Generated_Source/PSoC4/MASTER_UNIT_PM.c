/*******************************************************************************
* File Name: MASTER_UNIT.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "MASTER_UNIT.h"

static MASTER_UNIT_BACKUP_STRUCT  MASTER_UNIT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: MASTER_UNIT_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet MASTER_UNIT_SUT.c usage_MASTER_UNIT_Sleep_Wakeup
*******************************************************************************/
void MASTER_UNIT_Sleep(void)
{
    #if defined(MASTER_UNIT__PC)
        MASTER_UNIT_backup.pcState = MASTER_UNIT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            MASTER_UNIT_backup.usbState = MASTER_UNIT_CR1_REG;
            MASTER_UNIT_USB_POWER_REG |= MASTER_UNIT_USBIO_ENTER_SLEEP;
            MASTER_UNIT_CR1_REG &= MASTER_UNIT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MASTER_UNIT__SIO)
        MASTER_UNIT_backup.sioState = MASTER_UNIT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        MASTER_UNIT_SIO_REG &= (uint32)(~MASTER_UNIT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: MASTER_UNIT_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to MASTER_UNIT_Sleep() for an example usage.
*******************************************************************************/
void MASTER_UNIT_Wakeup(void)
{
    #if defined(MASTER_UNIT__PC)
        MASTER_UNIT_PC = MASTER_UNIT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            MASTER_UNIT_USB_POWER_REG &= MASTER_UNIT_USBIO_EXIT_SLEEP_PH1;
            MASTER_UNIT_CR1_REG = MASTER_UNIT_backup.usbState;
            MASTER_UNIT_USB_POWER_REG &= MASTER_UNIT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MASTER_UNIT__SIO)
        MASTER_UNIT_SIO_REG = MASTER_UNIT_backup.sioState;
    #endif
}


/* [] END OF FILE */
