/*******************************************************************************
* File Name: MASTER_UNIT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MASTER_UNIT_H) /* Pins MASTER_UNIT_H */
#define CY_PINS_MASTER_UNIT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MASTER_UNIT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} MASTER_UNIT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MASTER_UNIT_Read(void);
void    MASTER_UNIT_Write(uint8 value);
uint8   MASTER_UNIT_ReadDataReg(void);
#if defined(MASTER_UNIT__PC) || (CY_PSOC4_4200L) 
    void    MASTER_UNIT_SetDriveMode(uint8 mode);
#endif
void    MASTER_UNIT_SetInterruptMode(uint16 position, uint16 mode);
uint8   MASTER_UNIT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MASTER_UNIT_Sleep(void); 
void MASTER_UNIT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MASTER_UNIT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MASTER_UNIT_DRIVE_MODE_BITS        (3)
    #define MASTER_UNIT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MASTER_UNIT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MASTER_UNIT_SetDriveMode() function.
         *  @{
         */
        #define MASTER_UNIT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MASTER_UNIT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MASTER_UNIT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MASTER_UNIT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MASTER_UNIT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MASTER_UNIT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MASTER_UNIT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MASTER_UNIT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MASTER_UNIT_MASK               MASTER_UNIT__MASK
#define MASTER_UNIT_SHIFT              MASTER_UNIT__SHIFT
#define MASTER_UNIT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MASTER_UNIT_SetInterruptMode() function.
     *  @{
     */
        #define MASTER_UNIT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MASTER_UNIT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MASTER_UNIT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MASTER_UNIT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MASTER_UNIT__SIO)
    #define MASTER_UNIT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MASTER_UNIT__PC) && (CY_PSOC4_4200L)
    #define MASTER_UNIT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MASTER_UNIT_USBIO_DISABLE              ((uint32)(~MASTER_UNIT_USBIO_ENABLE))
    #define MASTER_UNIT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MASTER_UNIT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MASTER_UNIT_USBIO_ENTER_SLEEP          ((uint32)((1u << MASTER_UNIT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MASTER_UNIT_USBIO_SUSPEND_DEL_SHIFT)))
    #define MASTER_UNIT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MASTER_UNIT_USBIO_SUSPEND_SHIFT)))
    #define MASTER_UNIT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MASTER_UNIT_USBIO_SUSPEND_DEL_SHIFT)))
    #define MASTER_UNIT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MASTER_UNIT__PC)
    /* Port Configuration */
    #define MASTER_UNIT_PC                 (* (reg32 *) MASTER_UNIT__PC)
#endif
/* Pin State */
#define MASTER_UNIT_PS                     (* (reg32 *) MASTER_UNIT__PS)
/* Data Register */
#define MASTER_UNIT_DR                     (* (reg32 *) MASTER_UNIT__DR)
/* Input Buffer Disable Override */
#define MASTER_UNIT_INP_DIS                (* (reg32 *) MASTER_UNIT__PC2)

/* Interrupt configuration Registers */
#define MASTER_UNIT_INTCFG                 (* (reg32 *) MASTER_UNIT__INTCFG)
#define MASTER_UNIT_INTSTAT                (* (reg32 *) MASTER_UNIT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MASTER_UNIT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MASTER_UNIT__SIO)
    #define MASTER_UNIT_SIO_REG            (* (reg32 *) MASTER_UNIT__SIO)
#endif /* (MASTER_UNIT__SIO_CFG) */

/* USBIO registers */
#if !defined(MASTER_UNIT__PC) && (CY_PSOC4_4200L)
    #define MASTER_UNIT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MASTER_UNIT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MASTER_UNIT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MASTER_UNIT_DRIVE_MODE_SHIFT       (0x00u)
#define MASTER_UNIT_DRIVE_MODE_MASK        (0x07u << MASTER_UNIT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MASTER_UNIT_H */


/* [] END OF FILE */
