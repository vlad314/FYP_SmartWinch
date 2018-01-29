/*******************************************************************************
* File Name: Address.h  
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

#if !defined(CY_PINS_Address_H) /* Pins Address_H */
#define CY_PINS_Address_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Address_aliases.h"


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
} Address_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Address_Read(void);
void    Address_Write(uint8 value);
uint8   Address_ReadDataReg(void);
#if defined(Address__PC) || (CY_PSOC4_4200L) 
    void    Address_SetDriveMode(uint8 mode);
#endif
void    Address_SetInterruptMode(uint16 position, uint16 mode);
uint8   Address_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Address_Sleep(void); 
void Address_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Address__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Address_DRIVE_MODE_BITS        (3)
    #define Address_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Address_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Address_SetDriveMode() function.
         *  @{
         */
        #define Address_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Address_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Address_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Address_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Address_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Address_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Address_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Address_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Address_MASK               Address__MASK
#define Address_SHIFT              Address__SHIFT
#define Address_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Address_SetInterruptMode() function.
     *  @{
     */
        #define Address_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Address_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Address_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Address_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Address__SIO)
    #define Address_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Address__PC) && (CY_PSOC4_4200L)
    #define Address_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Address_USBIO_DISABLE              ((uint32)(~Address_USBIO_ENABLE))
    #define Address_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Address_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Address_USBIO_ENTER_SLEEP          ((uint32)((1u << Address_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Address_USBIO_SUSPEND_DEL_SHIFT)))
    #define Address_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Address_USBIO_SUSPEND_SHIFT)))
    #define Address_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Address_USBIO_SUSPEND_DEL_SHIFT)))
    #define Address_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Address__PC)
    /* Port Configuration */
    #define Address_PC                 (* (reg32 *) Address__PC)
#endif
/* Pin State */
#define Address_PS                     (* (reg32 *) Address__PS)
/* Data Register */
#define Address_DR                     (* (reg32 *) Address__DR)
/* Input Buffer Disable Override */
#define Address_INP_DIS                (* (reg32 *) Address__PC2)

/* Interrupt configuration Registers */
#define Address_INTCFG                 (* (reg32 *) Address__INTCFG)
#define Address_INTSTAT                (* (reg32 *) Address__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Address_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Address__SIO)
    #define Address_SIO_REG            (* (reg32 *) Address__SIO)
#endif /* (Address__SIO_CFG) */

/* USBIO registers */
#if !defined(Address__PC) && (CY_PSOC4_4200L)
    #define Address_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Address_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Address_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Address_DRIVE_MODE_SHIFT       (0x00u)
#define Address_DRIVE_MODE_MASK        (0x07u << Address_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Address_H */


/* [] END OF FILE */
