/*******************************************************************************
* File Name: ID.h  
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

#if !defined(CY_PINS_ID_H) /* Pins ID_H */
#define CY_PINS_ID_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ID_aliases.h"


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
} ID_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ID_Read(void);
void    ID_Write(uint8 value);
uint8   ID_ReadDataReg(void);
#if defined(ID__PC) || (CY_PSOC4_4200L) 
    void    ID_SetDriveMode(uint8 mode);
#endif
void    ID_SetInterruptMode(uint16 position, uint16 mode);
uint8   ID_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ID_Sleep(void); 
void ID_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ID__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ID_DRIVE_MODE_BITS        (3)
    #define ID_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ID_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ID_SetDriveMode() function.
         *  @{
         */
        #define ID_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ID_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ID_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ID_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ID_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ID_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ID_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ID_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ID_MASK               ID__MASK
#define ID_SHIFT              ID__SHIFT
#define ID_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ID_SetInterruptMode() function.
     *  @{
     */
        #define ID_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ID_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ID_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ID_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ID__SIO)
    #define ID_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ID__PC) && (CY_PSOC4_4200L)
    #define ID_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ID_USBIO_DISABLE              ((uint32)(~ID_USBIO_ENABLE))
    #define ID_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ID_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ID_USBIO_ENTER_SLEEP          ((uint32)((1u << ID_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ID_USBIO_SUSPEND_DEL_SHIFT)))
    #define ID_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ID_USBIO_SUSPEND_SHIFT)))
    #define ID_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ID_USBIO_SUSPEND_DEL_SHIFT)))
    #define ID_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ID__PC)
    /* Port Configuration */
    #define ID_PC                 (* (reg32 *) ID__PC)
#endif
/* Pin State */
#define ID_PS                     (* (reg32 *) ID__PS)
/* Data Register */
#define ID_DR                     (* (reg32 *) ID__DR)
/* Input Buffer Disable Override */
#define ID_INP_DIS                (* (reg32 *) ID__PC2)

/* Interrupt configuration Registers */
#define ID_INTCFG                 (* (reg32 *) ID__INTCFG)
#define ID_INTSTAT                (* (reg32 *) ID__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ID_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ID__SIO)
    #define ID_SIO_REG            (* (reg32 *) ID__SIO)
#endif /* (ID__SIO_CFG) */

/* USBIO registers */
#if !defined(ID__PC) && (CY_PSOC4_4200L)
    #define ID_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ID_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ID_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ID_DRIVE_MODE_SHIFT       (0x00u)
#define ID_DRIVE_MODE_MASK        (0x07u << ID_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ID_H */


/* [] END OF FILE */
