/*******************************************************************************
* File Name: ID.h  
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

#if !defined(CY_PINS_ID_ALIASES_H) /* Pins ID_ALIASES_H */
#define CY_PINS_ID_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ID_0			(ID__0__PC)
#define ID_0_PS		(ID__0__PS)
#define ID_0_PC		(ID__0__PC)
#define ID_0_DR		(ID__0__DR)
#define ID_0_SHIFT	(ID__0__SHIFT)
#define ID_0_INTR	((uint16)((uint16)0x0003u << (ID__0__SHIFT*2u)))

#define ID_INTR_ALL	 ((uint16)(ID_0_INTR))


#endif /* End Pins ID_ALIASES_H */


/* [] END OF FILE */
