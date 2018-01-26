/*******************************************************************************
* File Name: QE_A.h  
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

#if !defined(CY_PINS_QE_A_ALIASES_H) /* Pins QE_A_ALIASES_H */
#define CY_PINS_QE_A_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define QE_A_0			(QE_A__0__PC)
#define QE_A_0_PS		(QE_A__0__PS)
#define QE_A_0_PC		(QE_A__0__PC)
#define QE_A_0_DR		(QE_A__0__DR)
#define QE_A_0_SHIFT	(QE_A__0__SHIFT)
#define QE_A_0_INTR	((uint16)((uint16)0x0003u << (QE_A__0__SHIFT*2u)))

#define QE_A_INTR_ALL	 ((uint16)(QE_A_0_INTR))


#endif /* End Pins QE_A_ALIASES_H */


/* [] END OF FILE */
