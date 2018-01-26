/*******************************************************************************
* File Name: QE_B.h  
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

#if !defined(CY_PINS_QE_B_ALIASES_H) /* Pins QE_B_ALIASES_H */
#define CY_PINS_QE_B_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define QE_B_0			(QE_B__0__PC)
#define QE_B_0_PS		(QE_B__0__PS)
#define QE_B_0_PC		(QE_B__0__PC)
#define QE_B_0_DR		(QE_B__0__DR)
#define QE_B_0_SHIFT	(QE_B__0__SHIFT)
#define QE_B_0_INTR	((uint16)((uint16)0x0003u << (QE_B__0__SHIFT*2u)))

#define QE_B_INTR_ALL	 ((uint16)(QE_B_0_INTR))


#endif /* End Pins QE_B_ALIASES_H */


/* [] END OF FILE */
