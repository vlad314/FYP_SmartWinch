/*******************************************************************************
* File Name: Current_B.h  
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

#if !defined(CY_PINS_Current_B_ALIASES_H) /* Pins Current_B_ALIASES_H */
#define CY_PINS_Current_B_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Current_B_0			(Current_B__0__PC)
#define Current_B_0_PS		(Current_B__0__PS)
#define Current_B_0_PC		(Current_B__0__PC)
#define Current_B_0_DR		(Current_B__0__DR)
#define Current_B_0_SHIFT	(Current_B__0__SHIFT)
#define Current_B_0_INTR	((uint16)((uint16)0x0003u << (Current_B__0__SHIFT*2u)))

#define Current_B_INTR_ALL	 ((uint16)(Current_B_0_INTR))


#endif /* End Pins Current_B_ALIASES_H */


/* [] END OF FILE */
