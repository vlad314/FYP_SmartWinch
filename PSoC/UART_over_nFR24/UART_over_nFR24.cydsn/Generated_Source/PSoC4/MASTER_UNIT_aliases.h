/*******************************************************************************
* File Name: MASTER_UNIT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MASTER_UNIT_ALIASES_H) /* Pins MASTER_UNIT_ALIASES_H */
#define CY_PINS_MASTER_UNIT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MASTER_UNIT_0			(MASTER_UNIT__0__PC)
#define MASTER_UNIT_0_PS		(MASTER_UNIT__0__PS)
#define MASTER_UNIT_0_PC		(MASTER_UNIT__0__PC)
#define MASTER_UNIT_0_DR		(MASTER_UNIT__0__DR)
#define MASTER_UNIT_0_SHIFT	(MASTER_UNIT__0__SHIFT)
#define MASTER_UNIT_0_INTR	((uint16)((uint16)0x0003u << (MASTER_UNIT__0__SHIFT*2u)))

#define MASTER_UNIT_INTR_ALL	 ((uint16)(MASTER_UNIT_0_INTR))


#endif /* End Pins MASTER_UNIT_ALIASES_H */


/* [] END OF FILE */
