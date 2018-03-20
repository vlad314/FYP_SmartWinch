/*******************************************************************************
* File Name: UART_IN.h  
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

#if !defined(CY_PINS_UART_IN_H) /* Pins UART_IN_H */
#define CY_PINS_UART_IN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UART_IN_aliases.h"


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
} UART_IN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UART_IN_Read(void);
void    UART_IN_Write(uint8 value);
uint8   UART_IN_ReadDataReg(void);
#if defined(UART_IN__PC) || (CY_PSOC4_4200L) 
    void    UART_IN_SetDriveMode(uint8 mode);
#endif
void    UART_IN_SetInterruptMode(uint16 position, uint16 mode);
uint8   UART_IN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UART_IN_Sleep(void); 
void UART_IN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UART_IN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UART_IN_DRIVE_MODE_BITS        (3)
    #define UART_IN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UART_IN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UART_IN_SetDriveMode() function.
         *  @{
         */
        #define UART_IN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UART_IN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UART_IN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UART_IN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UART_IN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UART_IN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UART_IN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UART_IN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UART_IN_MASK               UART_IN__MASK
#define UART_IN_SHIFT              UART_IN__SHIFT
#define UART_IN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UART_IN_SetInterruptMode() function.
     *  @{
     */
        #define UART_IN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UART_IN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UART_IN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UART_IN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UART_IN__SIO)
    #define UART_IN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UART_IN__PC) && (CY_PSOC4_4200L)
    #define UART_IN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UART_IN_USBIO_DISABLE              ((uint32)(~UART_IN_USBIO_ENABLE))
    #define UART_IN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UART_IN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UART_IN_USBIO_ENTER_SLEEP          ((uint32)((1u << UART_IN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UART_IN_USBIO_SUSPEND_DEL_SHIFT)))
    #define UART_IN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UART_IN_USBIO_SUSPEND_SHIFT)))
    #define UART_IN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UART_IN_USBIO_SUSPEND_DEL_SHIFT)))
    #define UART_IN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UART_IN__PC)
    /* Port Configuration */
    #define UART_IN_PC                 (* (reg32 *) UART_IN__PC)
#endif
/* Pin State */
#define UART_IN_PS                     (* (reg32 *) UART_IN__PS)
/* Data Register */
#define UART_IN_DR                     (* (reg32 *) UART_IN__DR)
/* Input Buffer Disable Override */
#define UART_IN_INP_DIS                (* (reg32 *) UART_IN__PC2)

/* Interrupt configuration Registers */
#define UART_IN_INTCFG                 (* (reg32 *) UART_IN__INTCFG)
#define UART_IN_INTSTAT                (* (reg32 *) UART_IN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UART_IN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UART_IN__SIO)
    #define UART_IN_SIO_REG            (* (reg32 *) UART_IN__SIO)
#endif /* (UART_IN__SIO_CFG) */

/* USBIO registers */
#if !defined(UART_IN__PC) && (CY_PSOC4_4200L)
    #define UART_IN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UART_IN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UART_IN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UART_IN_DRIVE_MODE_SHIFT       (0x00u)
#define UART_IN_DRIVE_MODE_MASK        (0x07u << UART_IN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UART_IN_H */


/* [] END OF FILE */
