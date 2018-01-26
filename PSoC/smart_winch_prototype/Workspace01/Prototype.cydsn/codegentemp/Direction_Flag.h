/*******************************************************************************
* File Name: Direction_Flag.h  
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

#if !defined(CY_PINS_Direction_Flag_H) /* Pins Direction_Flag_H */
#define CY_PINS_Direction_Flag_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Direction_Flag_aliases.h"


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
} Direction_Flag_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Direction_Flag_Read(void);
void    Direction_Flag_Write(uint8 value);
uint8   Direction_Flag_ReadDataReg(void);
#if defined(Direction_Flag__PC) || (CY_PSOC4_4200L) 
    void    Direction_Flag_SetDriveMode(uint8 mode);
#endif
void    Direction_Flag_SetInterruptMode(uint16 position, uint16 mode);
uint8   Direction_Flag_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Direction_Flag_Sleep(void); 
void Direction_Flag_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Direction_Flag__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Direction_Flag_DRIVE_MODE_BITS        (3)
    #define Direction_Flag_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Direction_Flag_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Direction_Flag_SetDriveMode() function.
         *  @{
         */
        #define Direction_Flag_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Direction_Flag_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Direction_Flag_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Direction_Flag_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Direction_Flag_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Direction_Flag_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Direction_Flag_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Direction_Flag_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Direction_Flag_MASK               Direction_Flag__MASK
#define Direction_Flag_SHIFT              Direction_Flag__SHIFT
#define Direction_Flag_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Direction_Flag_SetInterruptMode() function.
     *  @{
     */
        #define Direction_Flag_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Direction_Flag_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Direction_Flag_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Direction_Flag_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Direction_Flag__SIO)
    #define Direction_Flag_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Direction_Flag__PC) && (CY_PSOC4_4200L)
    #define Direction_Flag_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Direction_Flag_USBIO_DISABLE              ((uint32)(~Direction_Flag_USBIO_ENABLE))
    #define Direction_Flag_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Direction_Flag_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Direction_Flag_USBIO_ENTER_SLEEP          ((uint32)((1u << Direction_Flag_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Direction_Flag_USBIO_SUSPEND_DEL_SHIFT)))
    #define Direction_Flag_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Direction_Flag_USBIO_SUSPEND_SHIFT)))
    #define Direction_Flag_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Direction_Flag_USBIO_SUSPEND_DEL_SHIFT)))
    #define Direction_Flag_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Direction_Flag__PC)
    /* Port Configuration */
    #define Direction_Flag_PC                 (* (reg32 *) Direction_Flag__PC)
#endif
/* Pin State */
#define Direction_Flag_PS                     (* (reg32 *) Direction_Flag__PS)
/* Data Register */
#define Direction_Flag_DR                     (* (reg32 *) Direction_Flag__DR)
/* Input Buffer Disable Override */
#define Direction_Flag_INP_DIS                (* (reg32 *) Direction_Flag__PC2)

/* Interrupt configuration Registers */
#define Direction_Flag_INTCFG                 (* (reg32 *) Direction_Flag__INTCFG)
#define Direction_Flag_INTSTAT                (* (reg32 *) Direction_Flag__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Direction_Flag_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Direction_Flag__SIO)
    #define Direction_Flag_SIO_REG            (* (reg32 *) Direction_Flag__SIO)
#endif /* (Direction_Flag__SIO_CFG) */

/* USBIO registers */
#if !defined(Direction_Flag__PC) && (CY_PSOC4_4200L)
    #define Direction_Flag_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Direction_Flag_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Direction_Flag_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Direction_Flag_DRIVE_MODE_SHIFT       (0x00u)
#define Direction_Flag_DRIVE_MODE_MASK        (0x07u << Direction_Flag_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Direction_Flag_H */


/* [] END OF FILE */
