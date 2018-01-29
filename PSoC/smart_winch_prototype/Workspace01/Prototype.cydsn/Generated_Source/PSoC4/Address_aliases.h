/*******************************************************************************
* File Name: Address.h  
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

#if !defined(CY_PINS_Address_ALIASES_H) /* Pins Address_ALIASES_H */
#define CY_PINS_Address_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Address_0			(Address__0__PC)
#define Address_0_PS		(Address__0__PS)
#define Address_0_PC		(Address__0__PC)
#define Address_0_DR		(Address__0__DR)
#define Address_0_SHIFT	(Address__0__SHIFT)
#define Address_0_INTR	((uint16)((uint16)0x0003u << (Address__0__SHIFT*2u)))

#define Address_INTR_ALL	 ((uint16)(Address_0_INTR))


#endif /* End Pins Address_ALIASES_H */


/* [] END OF FILE */
