/*******************************************************************************
* File Name: NRF_IRQ.h  
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

#if !defined(CY_PINS_NRF_IRQ_H) /* Pins NRF_IRQ_H */
#define CY_PINS_NRF_IRQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "NRF_IRQ_aliases.h"


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
} NRF_IRQ_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   NRF_IRQ_Read(void);
void    NRF_IRQ_Write(uint8 value);
uint8   NRF_IRQ_ReadDataReg(void);
#if defined(NRF_IRQ__PC) || (CY_PSOC4_4200L) 
    void    NRF_IRQ_SetDriveMode(uint8 mode);
#endif
void    NRF_IRQ_SetInterruptMode(uint16 position, uint16 mode);
uint8   NRF_IRQ_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void NRF_IRQ_Sleep(void); 
void NRF_IRQ_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(NRF_IRQ__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define NRF_IRQ_DRIVE_MODE_BITS        (3)
    #define NRF_IRQ_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - NRF_IRQ_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the NRF_IRQ_SetDriveMode() function.
         *  @{
         */
        #define NRF_IRQ_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define NRF_IRQ_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define NRF_IRQ_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define NRF_IRQ_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define NRF_IRQ_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define NRF_IRQ_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define NRF_IRQ_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define NRF_IRQ_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define NRF_IRQ_MASK               NRF_IRQ__MASK
#define NRF_IRQ_SHIFT              NRF_IRQ__SHIFT
#define NRF_IRQ_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NRF_IRQ_SetInterruptMode() function.
     *  @{
     */
        #define NRF_IRQ_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define NRF_IRQ_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define NRF_IRQ_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define NRF_IRQ_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(NRF_IRQ__SIO)
    #define NRF_IRQ_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(NRF_IRQ__PC) && (CY_PSOC4_4200L)
    #define NRF_IRQ_USBIO_ENABLE               ((uint32)0x80000000u)
    #define NRF_IRQ_USBIO_DISABLE              ((uint32)(~NRF_IRQ_USBIO_ENABLE))
    #define NRF_IRQ_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define NRF_IRQ_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define NRF_IRQ_USBIO_ENTER_SLEEP          ((uint32)((1u << NRF_IRQ_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << NRF_IRQ_USBIO_SUSPEND_DEL_SHIFT)))
    #define NRF_IRQ_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << NRF_IRQ_USBIO_SUSPEND_SHIFT)))
    #define NRF_IRQ_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << NRF_IRQ_USBIO_SUSPEND_DEL_SHIFT)))
    #define NRF_IRQ_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(NRF_IRQ__PC)
    /* Port Configuration */
    #define NRF_IRQ_PC                 (* (reg32 *) NRF_IRQ__PC)
#endif
/* Pin State */
#define NRF_IRQ_PS                     (* (reg32 *) NRF_IRQ__PS)
/* Data Register */
#define NRF_IRQ_DR                     (* (reg32 *) NRF_IRQ__DR)
/* Input Buffer Disable Override */
#define NRF_IRQ_INP_DIS                (* (reg32 *) NRF_IRQ__PC2)

/* Interrupt configuration Registers */
#define NRF_IRQ_INTCFG                 (* (reg32 *) NRF_IRQ__INTCFG)
#define NRF_IRQ_INTSTAT                (* (reg32 *) NRF_IRQ__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define NRF_IRQ_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(NRF_IRQ__SIO)
    #define NRF_IRQ_SIO_REG            (* (reg32 *) NRF_IRQ__SIO)
#endif /* (NRF_IRQ__SIO_CFG) */

/* USBIO registers */
#if !defined(NRF_IRQ__PC) && (CY_PSOC4_4200L)
    #define NRF_IRQ_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define NRF_IRQ_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define NRF_IRQ_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define NRF_IRQ_DRIVE_MODE_SHIFT       (0x00u)
#define NRF_IRQ_DRIVE_MODE_MASK        (0x07u << NRF_IRQ_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins NRF_IRQ_H */


/* [] END OF FILE */
