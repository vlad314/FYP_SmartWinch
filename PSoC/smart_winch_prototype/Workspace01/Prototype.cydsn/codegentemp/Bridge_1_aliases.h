/*******************************************************************************
* File Name: Bridge_1.h  
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

#if !defined(CY_PINS_Bridge_1_ALIASES_H) /* Pins Bridge_1_ALIASES_H */
#define CY_PINS_Bridge_1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Bridge_1_0			(Bridge_1__0__PC)
#define Bridge_1_0_PS		(Bridge_1__0__PS)
#define Bridge_1_0_PC		(Bridge_1__0__PC)
#define Bridge_1_0_DR		(Bridge_1__0__DR)
#define Bridge_1_0_SHIFT	(Bridge_1__0__SHIFT)
#define Bridge_1_0_INTR	((uint16)((uint16)0x0003u << (Bridge_1__0__SHIFT*2u)))

#define Bridge_1_INTR_ALL	 ((uint16)(Bridge_1_0_INTR))


#endif /* End Pins Bridge_1_ALIASES_H */


/* [] END OF FILE */
