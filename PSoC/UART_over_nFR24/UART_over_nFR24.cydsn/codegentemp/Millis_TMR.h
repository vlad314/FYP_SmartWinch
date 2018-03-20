/*******************************************************************************
* File Name: Millis_TMR.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Millis_TMR
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_Millis_TMR_H)
#define CY_TCPWM_Millis_TMR_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Millis_TMR_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Millis_TMR_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Millis_TMR_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Millis_TMR_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Millis_TMR_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Millis_TMR_QUAD_ENCODING_MODES            (0lu)
#define Millis_TMR_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Millis_TMR_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Millis_TMR_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Millis_TMR_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Millis_TMR_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Millis_TMR_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Millis_TMR_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Millis_TMR_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Millis_TMR_TC_RUN_MODE                    (0lu)
#define Millis_TMR_TC_COUNTER_MODE                (0lu)
#define Millis_TMR_TC_COMP_CAP_MODE               (2lu)
#define Millis_TMR_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Millis_TMR_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Millis_TMR_TC_COUNT_SIGNAL_MODE           (3lu)
#define Millis_TMR_TC_START_SIGNAL_MODE           (0lu)
#define Millis_TMR_TC_STOP_SIGNAL_MODE            (0lu)
#define Millis_TMR_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Millis_TMR_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Millis_TMR_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Millis_TMR_TC_START_SIGNAL_PRESENT        (0lu)
#define Millis_TMR_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Millis_TMR_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Millis_TMR_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Millis_TMR_PWM_KILL_EVENT                 (0lu)
#define Millis_TMR_PWM_STOP_EVENT                 (0lu)
#define Millis_TMR_PWM_MODE                       (4lu)
#define Millis_TMR_PWM_OUT_N_INVERT               (0lu)
#define Millis_TMR_PWM_OUT_INVERT                 (0lu)
#define Millis_TMR_PWM_ALIGN                      (0lu)
#define Millis_TMR_PWM_RUN_MODE                   (0lu)
#define Millis_TMR_PWM_DEAD_TIME_CYCLE            (0lu)
#define Millis_TMR_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Millis_TMR_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Millis_TMR_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Millis_TMR_PWM_START_SIGNAL_MODE          (0lu)
#define Millis_TMR_PWM_STOP_SIGNAL_MODE           (0lu)
#define Millis_TMR_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Millis_TMR_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Millis_TMR_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Millis_TMR_PWM_START_SIGNAL_PRESENT       (0lu)
#define Millis_TMR_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Millis_TMR_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Millis_TMR_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Millis_TMR_TC_PERIOD_VALUE                (1000lu)
#define Millis_TMR_TC_COMPARE_VALUE               (65535lu)
#define Millis_TMR_TC_COMPARE_BUF_VALUE           (65535lu)
#define Millis_TMR_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Millis_TMR_PWM_PERIOD_VALUE               (65535lu)
#define Millis_TMR_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Millis_TMR_PWM_PERIOD_SWAP                (0lu)
#define Millis_TMR_PWM_COMPARE_VALUE              (65535lu)
#define Millis_TMR_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Millis_TMR_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Millis_TMR__LEFT 0
#define Millis_TMR__RIGHT 1
#define Millis_TMR__CENTER 2
#define Millis_TMR__ASYMMETRIC 3

#define Millis_TMR__X1 0
#define Millis_TMR__X2 1
#define Millis_TMR__X4 2

#define Millis_TMR__PWM 4
#define Millis_TMR__PWM_DT 5
#define Millis_TMR__PWM_PR 6

#define Millis_TMR__INVERSE 1
#define Millis_TMR__DIRECT 0

#define Millis_TMR__CAPTURE 2
#define Millis_TMR__COMPARE 0

#define Millis_TMR__TRIG_LEVEL 3
#define Millis_TMR__TRIG_RISING 0
#define Millis_TMR__TRIG_FALLING 1
#define Millis_TMR__TRIG_BOTH 2

#define Millis_TMR__INTR_MASK_TC 1
#define Millis_TMR__INTR_MASK_CC_MATCH 2
#define Millis_TMR__INTR_MASK_NONE 0
#define Millis_TMR__INTR_MASK_TC_CC 3

#define Millis_TMR__UNCONFIG 8
#define Millis_TMR__TIMER 1
#define Millis_TMR__QUAD 3
#define Millis_TMR__PWM_SEL 7

#define Millis_TMR__COUNT_UP 0
#define Millis_TMR__COUNT_DOWN 1
#define Millis_TMR__COUNT_UPDOWN0 2
#define Millis_TMR__COUNT_UPDOWN1 3


/* Prescaler */
#define Millis_TMR_PRESCALE_DIVBY1                ((uint32)(0u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY2                ((uint32)(1u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY4                ((uint32)(2u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY8                ((uint32)(3u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY16               ((uint32)(4u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY32               ((uint32)(5u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY64               ((uint32)(6u << Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_PRESCALE_DIVBY128              ((uint32)(7u << Millis_TMR_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Millis_TMR_MODE_TIMER_COMPARE             ((uint32)(Millis_TMR__COMPARE         <<  \
                                                                  Millis_TMR_MODE_SHIFT))
#define Millis_TMR_MODE_TIMER_CAPTURE             ((uint32)(Millis_TMR__CAPTURE         <<  \
                                                                  Millis_TMR_MODE_SHIFT))
#define Millis_TMR_MODE_QUAD                      ((uint32)(Millis_TMR__QUAD            <<  \
                                                                  Millis_TMR_MODE_SHIFT))
#define Millis_TMR_MODE_PWM                       ((uint32)(Millis_TMR__PWM             <<  \
                                                                  Millis_TMR_MODE_SHIFT))
#define Millis_TMR_MODE_PWM_DT                    ((uint32)(Millis_TMR__PWM_DT          <<  \
                                                                  Millis_TMR_MODE_SHIFT))
#define Millis_TMR_MODE_PWM_PR                    ((uint32)(Millis_TMR__PWM_PR          <<  \
                                                                  Millis_TMR_MODE_SHIFT))

/* Quad Modes */
#define Millis_TMR_MODE_X1                        ((uint32)(Millis_TMR__X1              <<  \
                                                                  Millis_TMR_QUAD_MODE_SHIFT))
#define Millis_TMR_MODE_X2                        ((uint32)(Millis_TMR__X2              <<  \
                                                                  Millis_TMR_QUAD_MODE_SHIFT))
#define Millis_TMR_MODE_X4                        ((uint32)(Millis_TMR__X4              <<  \
                                                                  Millis_TMR_QUAD_MODE_SHIFT))

/* Counter modes */
#define Millis_TMR_COUNT_UP                       ((uint32)(Millis_TMR__COUNT_UP        <<  \
                                                                  Millis_TMR_UPDOWN_SHIFT))
#define Millis_TMR_COUNT_DOWN                     ((uint32)(Millis_TMR__COUNT_DOWN      <<  \
                                                                  Millis_TMR_UPDOWN_SHIFT))
#define Millis_TMR_COUNT_UPDOWN0                  ((uint32)(Millis_TMR__COUNT_UPDOWN0   <<  \
                                                                  Millis_TMR_UPDOWN_SHIFT))
#define Millis_TMR_COUNT_UPDOWN1                  ((uint32)(Millis_TMR__COUNT_UPDOWN1   <<  \
                                                                  Millis_TMR_UPDOWN_SHIFT))

/* PWM output invert */
#define Millis_TMR_INVERT_LINE                    ((uint32)(Millis_TMR__INVERSE         <<  \
                                                                  Millis_TMR_INV_OUT_SHIFT))
#define Millis_TMR_INVERT_LINE_N                  ((uint32)(Millis_TMR__INVERSE         <<  \
                                                                  Millis_TMR_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Millis_TMR_TRIG_RISING                    ((uint32)Millis_TMR__TRIG_RISING)
#define Millis_TMR_TRIG_FALLING                   ((uint32)Millis_TMR__TRIG_FALLING)
#define Millis_TMR_TRIG_BOTH                      ((uint32)Millis_TMR__TRIG_BOTH)
#define Millis_TMR_TRIG_LEVEL                     ((uint32)Millis_TMR__TRIG_LEVEL)

/* Interrupt mask */
#define Millis_TMR_INTR_MASK_TC                   ((uint32)Millis_TMR__INTR_MASK_TC)
#define Millis_TMR_INTR_MASK_CC_MATCH             ((uint32)Millis_TMR__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Millis_TMR_CC_MATCH_SET                   (0x00u)
#define Millis_TMR_CC_MATCH_CLEAR                 (0x01u)
#define Millis_TMR_CC_MATCH_INVERT                (0x02u)
#define Millis_TMR_CC_MATCH_NO_CHANGE             (0x03u)
#define Millis_TMR_OVERLOW_SET                    (0x00u)
#define Millis_TMR_OVERLOW_CLEAR                  (0x04u)
#define Millis_TMR_OVERLOW_INVERT                 (0x08u)
#define Millis_TMR_OVERLOW_NO_CHANGE              (0x0Cu)
#define Millis_TMR_UNDERFLOW_SET                  (0x00u)
#define Millis_TMR_UNDERFLOW_CLEAR                (0x10u)
#define Millis_TMR_UNDERFLOW_INVERT               (0x20u)
#define Millis_TMR_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Millis_TMR_PWM_MODE_LEFT                  (Millis_TMR_CC_MATCH_CLEAR        |   \
                                                         Millis_TMR_OVERLOW_SET           |   \
                                                         Millis_TMR_UNDERFLOW_NO_CHANGE)
#define Millis_TMR_PWM_MODE_RIGHT                 (Millis_TMR_CC_MATCH_SET          |   \
                                                         Millis_TMR_OVERLOW_NO_CHANGE     |   \
                                                         Millis_TMR_UNDERFLOW_CLEAR)
#define Millis_TMR_PWM_MODE_ASYM                  (Millis_TMR_CC_MATCH_INVERT       |   \
                                                         Millis_TMR_OVERLOW_SET           |   \
                                                         Millis_TMR_UNDERFLOW_CLEAR)

#if (Millis_TMR_CY_TCPWM_V2)
    #if(Millis_TMR_CY_TCPWM_4000)
        #define Millis_TMR_PWM_MODE_CENTER                (Millis_TMR_CC_MATCH_INVERT       |   \
                                                                 Millis_TMR_OVERLOW_NO_CHANGE     |   \
                                                                 Millis_TMR_UNDERFLOW_CLEAR)
    #else
        #define Millis_TMR_PWM_MODE_CENTER                (Millis_TMR_CC_MATCH_INVERT       |   \
                                                                 Millis_TMR_OVERLOW_SET           |   \
                                                                 Millis_TMR_UNDERFLOW_CLEAR)
    #endif /* (Millis_TMR_CY_TCPWM_4000) */
#else
    #define Millis_TMR_PWM_MODE_CENTER                (Millis_TMR_CC_MATCH_INVERT       |   \
                                                             Millis_TMR_OVERLOW_NO_CHANGE     |   \
                                                             Millis_TMR_UNDERFLOW_CLEAR)
#endif /* (Millis_TMR_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Millis_TMR_CMD_CAPTURE                    (0u)
#define Millis_TMR_CMD_RELOAD                     (8u)
#define Millis_TMR_CMD_STOP                       (16u)
#define Millis_TMR_CMD_START                      (24u)

/* Status */
#define Millis_TMR_STATUS_DOWN                    (1u)
#define Millis_TMR_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Millis_TMR_Init(void);
void   Millis_TMR_Enable(void);
void   Millis_TMR_Start(void);
void   Millis_TMR_Stop(void);

void   Millis_TMR_SetMode(uint32 mode);
void   Millis_TMR_SetCounterMode(uint32 counterMode);
void   Millis_TMR_SetPWMMode(uint32 modeMask);
void   Millis_TMR_SetQDMode(uint32 qdMode);

void   Millis_TMR_SetPrescaler(uint32 prescaler);
void   Millis_TMR_TriggerCommand(uint32 mask, uint32 command);
void   Millis_TMR_SetOneShot(uint32 oneShotEnable);
uint32 Millis_TMR_ReadStatus(void);

void   Millis_TMR_SetPWMSyncKill(uint32 syncKillEnable);
void   Millis_TMR_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Millis_TMR_SetPWMDeadTime(uint32 deadTime);
void   Millis_TMR_SetPWMInvert(uint32 mask);

void   Millis_TMR_SetInterruptMode(uint32 interruptMask);
uint32 Millis_TMR_GetInterruptSourceMasked(void);
uint32 Millis_TMR_GetInterruptSource(void);
void   Millis_TMR_ClearInterrupt(uint32 interruptMask);
void   Millis_TMR_SetInterrupt(uint32 interruptMask);

void   Millis_TMR_WriteCounter(uint32 count);
uint32 Millis_TMR_ReadCounter(void);

uint32 Millis_TMR_ReadCapture(void);
uint32 Millis_TMR_ReadCaptureBuf(void);

void   Millis_TMR_WritePeriod(uint32 period);
uint32 Millis_TMR_ReadPeriod(void);
void   Millis_TMR_WritePeriodBuf(uint32 periodBuf);
uint32 Millis_TMR_ReadPeriodBuf(void);

void   Millis_TMR_WriteCompare(uint32 compare);
uint32 Millis_TMR_ReadCompare(void);
void   Millis_TMR_WriteCompareBuf(uint32 compareBuf);
uint32 Millis_TMR_ReadCompareBuf(void);

void   Millis_TMR_SetPeriodSwap(uint32 swapEnable);
void   Millis_TMR_SetCompareSwap(uint32 swapEnable);

void   Millis_TMR_SetCaptureMode(uint32 triggerMode);
void   Millis_TMR_SetReloadMode(uint32 triggerMode);
void   Millis_TMR_SetStartMode(uint32 triggerMode);
void   Millis_TMR_SetStopMode(uint32 triggerMode);
void   Millis_TMR_SetCountMode(uint32 triggerMode);

void   Millis_TMR_SaveConfig(void);
void   Millis_TMR_RestoreConfig(void);
void   Millis_TMR_Sleep(void);
void   Millis_TMR_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Millis_TMR_BLOCK_CONTROL_REG              (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Millis_TMR_BLOCK_CONTROL_PTR              ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Millis_TMR_COMMAND_REG                    (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Millis_TMR_COMMAND_PTR                    ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Millis_TMR_INTRRUPT_CAUSE_REG             (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Millis_TMR_INTRRUPT_CAUSE_PTR             ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Millis_TMR_CONTROL_REG                    (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__CTRL )
#define Millis_TMR_CONTROL_PTR                    ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__CTRL )
#define Millis_TMR_STATUS_REG                     (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__STATUS )
#define Millis_TMR_STATUS_PTR                     ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__STATUS )
#define Millis_TMR_COUNTER_REG                    (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__COUNTER )
#define Millis_TMR_COUNTER_PTR                    ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__COUNTER )
#define Millis_TMR_COMP_CAP_REG                   (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__CC )
#define Millis_TMR_COMP_CAP_PTR                   ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__CC )
#define Millis_TMR_COMP_CAP_BUF_REG               (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__CC_BUFF )
#define Millis_TMR_COMP_CAP_BUF_PTR               ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__CC_BUFF )
#define Millis_TMR_PERIOD_REG                     (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__PERIOD )
#define Millis_TMR_PERIOD_PTR                     ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__PERIOD )
#define Millis_TMR_PERIOD_BUF_REG                 (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Millis_TMR_PERIOD_BUF_PTR                 ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Millis_TMR_TRIG_CONTROL0_REG              (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Millis_TMR_TRIG_CONTROL0_PTR              ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Millis_TMR_TRIG_CONTROL1_REG              (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Millis_TMR_TRIG_CONTROL1_PTR              ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Millis_TMR_TRIG_CONTROL2_REG              (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Millis_TMR_TRIG_CONTROL2_PTR              ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Millis_TMR_INTERRUPT_REQ_REG              (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR )
#define Millis_TMR_INTERRUPT_REQ_PTR              ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR )
#define Millis_TMR_INTERRUPT_SET_REG              (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR_SET )
#define Millis_TMR_INTERRUPT_SET_PTR              ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR_SET )
#define Millis_TMR_INTERRUPT_MASK_REG             (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR_MASK )
#define Millis_TMR_INTERRUPT_MASK_PTR             ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR_MASK )
#define Millis_TMR_INTERRUPT_MASKED_REG           (*(reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Millis_TMR_INTERRUPT_MASKED_PTR           ( (reg32 *) Millis_TMR_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Millis_TMR_MASK                           ((uint32)Millis_TMR_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Millis_TMR_RELOAD_CC_SHIFT                (0u)
#define Millis_TMR_RELOAD_PERIOD_SHIFT            (1u)
#define Millis_TMR_PWM_SYNC_KILL_SHIFT            (2u)
#define Millis_TMR_PWM_STOP_KILL_SHIFT            (3u)
#define Millis_TMR_PRESCALER_SHIFT                (8u)
#define Millis_TMR_UPDOWN_SHIFT                   (16u)
#define Millis_TMR_ONESHOT_SHIFT                  (18u)
#define Millis_TMR_QUAD_MODE_SHIFT                (20u)
#define Millis_TMR_INV_OUT_SHIFT                  (20u)
#define Millis_TMR_INV_COMPL_OUT_SHIFT            (21u)
#define Millis_TMR_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Millis_TMR_RELOAD_CC_MASK                 ((uint32)(Millis_TMR_1BIT_MASK        <<  \
                                                                            Millis_TMR_RELOAD_CC_SHIFT))
#define Millis_TMR_RELOAD_PERIOD_MASK             ((uint32)(Millis_TMR_1BIT_MASK        <<  \
                                                                            Millis_TMR_RELOAD_PERIOD_SHIFT))
#define Millis_TMR_PWM_SYNC_KILL_MASK             ((uint32)(Millis_TMR_1BIT_MASK        <<  \
                                                                            Millis_TMR_PWM_SYNC_KILL_SHIFT))
#define Millis_TMR_PWM_STOP_KILL_MASK             ((uint32)(Millis_TMR_1BIT_MASK        <<  \
                                                                            Millis_TMR_PWM_STOP_KILL_SHIFT))
#define Millis_TMR_PRESCALER_MASK                 ((uint32)(Millis_TMR_8BIT_MASK        <<  \
                                                                            Millis_TMR_PRESCALER_SHIFT))
#define Millis_TMR_UPDOWN_MASK                    ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                            Millis_TMR_UPDOWN_SHIFT))
#define Millis_TMR_ONESHOT_MASK                   ((uint32)(Millis_TMR_1BIT_MASK        <<  \
                                                                            Millis_TMR_ONESHOT_SHIFT))
#define Millis_TMR_QUAD_MODE_MASK                 ((uint32)(Millis_TMR_3BIT_MASK        <<  \
                                                                            Millis_TMR_QUAD_MODE_SHIFT))
#define Millis_TMR_INV_OUT_MASK                   ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                            Millis_TMR_INV_OUT_SHIFT))
#define Millis_TMR_MODE_MASK                      ((uint32)(Millis_TMR_3BIT_MASK        <<  \
                                                                            Millis_TMR_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Millis_TMR_CAPTURE_SHIFT                  (0u)
#define Millis_TMR_COUNT_SHIFT                    (2u)
#define Millis_TMR_RELOAD_SHIFT                   (4u)
#define Millis_TMR_STOP_SHIFT                     (6u)
#define Millis_TMR_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Millis_TMR_CAPTURE_MASK                   ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                  Millis_TMR_CAPTURE_SHIFT))
#define Millis_TMR_COUNT_MASK                     ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                  Millis_TMR_COUNT_SHIFT))
#define Millis_TMR_RELOAD_MASK                    ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                  Millis_TMR_RELOAD_SHIFT))
#define Millis_TMR_STOP_MASK                      ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                  Millis_TMR_STOP_SHIFT))
#define Millis_TMR_START_MASK                     ((uint32)(Millis_TMR_2BIT_MASK        <<  \
                                                                  Millis_TMR_START_SHIFT))

/* MASK */
#define Millis_TMR_1BIT_MASK                      ((uint32)0x01u)
#define Millis_TMR_2BIT_MASK                      ((uint32)0x03u)
#define Millis_TMR_3BIT_MASK                      ((uint32)0x07u)
#define Millis_TMR_6BIT_MASK                      ((uint32)0x3Fu)
#define Millis_TMR_8BIT_MASK                      ((uint32)0xFFu)
#define Millis_TMR_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Millis_TMR_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Millis_TMR_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Millis_TMR_QUAD_ENCODING_MODES     << Millis_TMR_QUAD_MODE_SHIFT))       |\
         ((uint32)(Millis_TMR_CONFIG                  << Millis_TMR_MODE_SHIFT)))

#define Millis_TMR_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Millis_TMR_PWM_STOP_EVENT          << Millis_TMR_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Millis_TMR_PWM_OUT_INVERT          << Millis_TMR_INV_OUT_SHIFT))         |\
         ((uint32)(Millis_TMR_PWM_OUT_N_INVERT        << Millis_TMR_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Millis_TMR_PWM_MODE                << Millis_TMR_MODE_SHIFT)))

#define Millis_TMR_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Millis_TMR_PWM_RUN_MODE         << Millis_TMR_ONESHOT_SHIFT))
            
#define Millis_TMR_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Millis_TMR_PWM_ALIGN            << Millis_TMR_UPDOWN_SHIFT))

#define Millis_TMR_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Millis_TMR_PWM_KILL_EVENT      << Millis_TMR_PWM_SYNC_KILL_SHIFT))

#define Millis_TMR_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Millis_TMR_PWM_DEAD_TIME_CYCLE  << Millis_TMR_PRESCALER_SHIFT))

#define Millis_TMR_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Millis_TMR_PWM_PRESCALER        << Millis_TMR_PRESCALER_SHIFT))

#define Millis_TMR_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Millis_TMR_TC_PRESCALER            << Millis_TMR_PRESCALER_SHIFT))       |\
         ((uint32)(Millis_TMR_TC_COUNTER_MODE         << Millis_TMR_UPDOWN_SHIFT))          |\
         ((uint32)(Millis_TMR_TC_RUN_MODE             << Millis_TMR_ONESHOT_SHIFT))         |\
         ((uint32)(Millis_TMR_TC_COMP_CAP_MODE        << Millis_TMR_MODE_SHIFT)))
        
#define Millis_TMR_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Millis_TMR_QUAD_PHIA_SIGNAL_MODE   << Millis_TMR_COUNT_SHIFT))           |\
         ((uint32)(Millis_TMR_QUAD_INDEX_SIGNAL_MODE  << Millis_TMR_RELOAD_SHIFT))          |\
         ((uint32)(Millis_TMR_QUAD_STOP_SIGNAL_MODE   << Millis_TMR_STOP_SHIFT))            |\
         ((uint32)(Millis_TMR_QUAD_PHIB_SIGNAL_MODE   << Millis_TMR_START_SHIFT)))

#define Millis_TMR_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Millis_TMR_PWM_SWITCH_SIGNAL_MODE  << Millis_TMR_CAPTURE_SHIFT))         |\
         ((uint32)(Millis_TMR_PWM_COUNT_SIGNAL_MODE   << Millis_TMR_COUNT_SHIFT))           |\
         ((uint32)(Millis_TMR_PWM_RELOAD_SIGNAL_MODE  << Millis_TMR_RELOAD_SHIFT))          |\
         ((uint32)(Millis_TMR_PWM_STOP_SIGNAL_MODE    << Millis_TMR_STOP_SHIFT))            |\
         ((uint32)(Millis_TMR_PWM_START_SIGNAL_MODE   << Millis_TMR_START_SHIFT)))

#define Millis_TMR_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Millis_TMR_TC_CAPTURE_SIGNAL_MODE  << Millis_TMR_CAPTURE_SHIFT))         |\
         ((uint32)(Millis_TMR_TC_COUNT_SIGNAL_MODE    << Millis_TMR_COUNT_SHIFT))           |\
         ((uint32)(Millis_TMR_TC_RELOAD_SIGNAL_MODE   << Millis_TMR_RELOAD_SHIFT))          |\
         ((uint32)(Millis_TMR_TC_STOP_SIGNAL_MODE     << Millis_TMR_STOP_SHIFT))            |\
         ((uint32)(Millis_TMR_TC_START_SIGNAL_MODE    << Millis_TMR_START_SHIFT)))
        
#define Millis_TMR_TIMER_UPDOWN_CNT_USED                                                          \
                ((Millis_TMR__COUNT_UPDOWN0 == Millis_TMR_TC_COUNTER_MODE)                  ||\
                 (Millis_TMR__COUNT_UPDOWN1 == Millis_TMR_TC_COUNTER_MODE))

#define Millis_TMR_PWM_UPDOWN_CNT_USED                                                            \
                ((Millis_TMR__CENTER == Millis_TMR_PWM_ALIGN)                               ||\
                 (Millis_TMR__ASYMMETRIC == Millis_TMR_PWM_ALIGN))               
        
#define Millis_TMR_PWM_PR_INIT_VALUE              (1u)
#define Millis_TMR_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Millis_TMR_H */

/* [] END OF FILE */
