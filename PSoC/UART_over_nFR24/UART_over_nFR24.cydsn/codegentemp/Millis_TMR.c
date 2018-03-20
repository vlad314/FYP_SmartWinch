/*******************************************************************************
* File Name: Millis_TMR.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Millis_TMR
*  component
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

#include "Millis_TMR.h"

uint8 Millis_TMR_initVar = 0u;


/*******************************************************************************
* Function Name: Millis_TMR_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Millis_TMR configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Millis_TMR__QUAD == Millis_TMR_CONFIG)
        Millis_TMR_CONTROL_REG = Millis_TMR_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Millis_TMR_TRIG_CONTROL1_REG  = Millis_TMR_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Millis_TMR_SetInterruptMode(Millis_TMR_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Millis_TMR_SetCounterMode(Millis_TMR_COUNT_DOWN);
        Millis_TMR_WritePeriod(Millis_TMR_QUAD_PERIOD_INIT_VALUE);
        Millis_TMR_WriteCounter(Millis_TMR_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Millis_TMR__QUAD == Millis_TMR_CONFIG) */

    #if (Millis_TMR__TIMER == Millis_TMR_CONFIG)
        Millis_TMR_CONTROL_REG = Millis_TMR_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Millis_TMR_TRIG_CONTROL1_REG  = Millis_TMR_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Millis_TMR_SetInterruptMode(Millis_TMR_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Millis_TMR_WritePeriod(Millis_TMR_TC_PERIOD_VALUE );

        #if (Millis_TMR__COMPARE == Millis_TMR_TC_COMP_CAP_MODE)
            Millis_TMR_WriteCompare(Millis_TMR_TC_COMPARE_VALUE);

            #if (1u == Millis_TMR_TC_COMPARE_SWAP)
                Millis_TMR_SetCompareSwap(1u);
                Millis_TMR_WriteCompareBuf(Millis_TMR_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Millis_TMR_TC_COMPARE_SWAP) */
        #endif  /* (Millis_TMR__COMPARE == Millis_TMR_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Millis_TMR_CY_TCPWM_V2 && Millis_TMR_TIMER_UPDOWN_CNT_USED && !Millis_TMR_CY_TCPWM_4000)
            Millis_TMR_WriteCounter(1u);
        #elif(Millis_TMR__COUNT_DOWN == Millis_TMR_TC_COUNTER_MODE)
            Millis_TMR_WriteCounter(Millis_TMR_TC_PERIOD_VALUE);
        #else
            Millis_TMR_WriteCounter(0u);
        #endif /* (Millis_TMR_CY_TCPWM_V2 && Millis_TMR_TIMER_UPDOWN_CNT_USED && !Millis_TMR_CY_TCPWM_4000) */
    #endif  /* (Millis_TMR__TIMER == Millis_TMR_CONFIG) */

    #if (Millis_TMR__PWM_SEL == Millis_TMR_CONFIG)
        Millis_TMR_CONTROL_REG = Millis_TMR_CTRL_PWM_BASE_CONFIG;

        #if (Millis_TMR__PWM_PR == Millis_TMR_PWM_MODE)
            Millis_TMR_CONTROL_REG |= Millis_TMR_CTRL_PWM_RUN_MODE;
            Millis_TMR_WriteCounter(Millis_TMR_PWM_PR_INIT_VALUE);
        #else
            Millis_TMR_CONTROL_REG |= Millis_TMR_CTRL_PWM_ALIGN | Millis_TMR_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Millis_TMR_CY_TCPWM_V2 && Millis_TMR_PWM_UPDOWN_CNT_USED && !Millis_TMR_CY_TCPWM_4000)
                Millis_TMR_WriteCounter(1u);
            #elif (Millis_TMR__RIGHT == Millis_TMR_PWM_ALIGN)
                Millis_TMR_WriteCounter(Millis_TMR_PWM_PERIOD_VALUE);
            #else 
                Millis_TMR_WriteCounter(0u);
            #endif  /* (Millis_TMR_CY_TCPWM_V2 && Millis_TMR_PWM_UPDOWN_CNT_USED && !Millis_TMR_CY_TCPWM_4000) */
        #endif  /* (Millis_TMR__PWM_PR == Millis_TMR_PWM_MODE) */

        #if (Millis_TMR__PWM_DT == Millis_TMR_PWM_MODE)
            Millis_TMR_CONTROL_REG |= Millis_TMR_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Millis_TMR__PWM_DT == Millis_TMR_PWM_MODE) */

        #if (Millis_TMR__PWM == Millis_TMR_PWM_MODE)
            Millis_TMR_CONTROL_REG |= Millis_TMR_CTRL_PWM_PRESCALER;
        #endif  /* (Millis_TMR__PWM == Millis_TMR_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Millis_TMR_TRIG_CONTROL1_REG  = Millis_TMR_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Millis_TMR_SetInterruptMode(Millis_TMR_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Millis_TMR__PWM_PR == Millis_TMR_PWM_MODE)
            Millis_TMR_TRIG_CONTROL2_REG =
                    (Millis_TMR_CC_MATCH_NO_CHANGE    |
                    Millis_TMR_OVERLOW_NO_CHANGE      |
                    Millis_TMR_UNDERFLOW_NO_CHANGE);
        #else
            #if (Millis_TMR__LEFT == Millis_TMR_PWM_ALIGN)
                Millis_TMR_TRIG_CONTROL2_REG = Millis_TMR_PWM_MODE_LEFT;
            #endif  /* ( Millis_TMR_PWM_LEFT == Millis_TMR_PWM_ALIGN) */

            #if (Millis_TMR__RIGHT == Millis_TMR_PWM_ALIGN)
                Millis_TMR_TRIG_CONTROL2_REG = Millis_TMR_PWM_MODE_RIGHT;
            #endif  /* ( Millis_TMR_PWM_RIGHT == Millis_TMR_PWM_ALIGN) */

            #if (Millis_TMR__CENTER == Millis_TMR_PWM_ALIGN)
                Millis_TMR_TRIG_CONTROL2_REG = Millis_TMR_PWM_MODE_CENTER;
            #endif  /* ( Millis_TMR_PWM_CENTER == Millis_TMR_PWM_ALIGN) */

            #if (Millis_TMR__ASYMMETRIC == Millis_TMR_PWM_ALIGN)
                Millis_TMR_TRIG_CONTROL2_REG = Millis_TMR_PWM_MODE_ASYM;
            #endif  /* (Millis_TMR__ASYMMETRIC == Millis_TMR_PWM_ALIGN) */
        #endif  /* (Millis_TMR__PWM_PR == Millis_TMR_PWM_MODE) */

        /* Set other values from customizer */
        Millis_TMR_WritePeriod(Millis_TMR_PWM_PERIOD_VALUE );
        Millis_TMR_WriteCompare(Millis_TMR_PWM_COMPARE_VALUE);

        #if (1u == Millis_TMR_PWM_COMPARE_SWAP)
            Millis_TMR_SetCompareSwap(1u);
            Millis_TMR_WriteCompareBuf(Millis_TMR_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Millis_TMR_PWM_COMPARE_SWAP) */

        #if (1u == Millis_TMR_PWM_PERIOD_SWAP)
            Millis_TMR_SetPeriodSwap(1u);
            Millis_TMR_WritePeriodBuf(Millis_TMR_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Millis_TMR_PWM_PERIOD_SWAP) */
    #endif  /* (Millis_TMR__PWM_SEL == Millis_TMR_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Millis_TMR_Enable
********************************************************************************
*
* Summary:
*  Enables the Millis_TMR.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Millis_TMR_BLOCK_CONTROL_REG |= Millis_TMR_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Millis_TMR__PWM_SEL == Millis_TMR_CONFIG)
        #if (0u == Millis_TMR_PWM_START_SIGNAL_PRESENT)
            Millis_TMR_TriggerCommand(Millis_TMR_MASK, Millis_TMR_CMD_START);
        #endif /* (0u == Millis_TMR_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Millis_TMR__PWM_SEL == Millis_TMR_CONFIG) */

    #if (Millis_TMR__TIMER == Millis_TMR_CONFIG)
        #if (0u == Millis_TMR_TC_START_SIGNAL_PRESENT)
            Millis_TMR_TriggerCommand(Millis_TMR_MASK, Millis_TMR_CMD_START);
        #endif /* (0u == Millis_TMR_TC_START_SIGNAL_PRESENT) */
    #endif /* (Millis_TMR__TIMER == Millis_TMR_CONFIG) */
    
    #if (Millis_TMR__QUAD == Millis_TMR_CONFIG)
        #if (0u != Millis_TMR_QUAD_AUTO_START)
            Millis_TMR_TriggerCommand(Millis_TMR_MASK, Millis_TMR_CMD_RELOAD);
        #endif /* (0u != Millis_TMR_QUAD_AUTO_START) */
    #endif  /* (Millis_TMR__QUAD == Millis_TMR_CONFIG) */
}


/*******************************************************************************
* Function Name: Millis_TMR_Start
********************************************************************************
*
* Summary:
*  Initializes the Millis_TMR with default customizer
*  values when called the first time and enables the Millis_TMR.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Millis_TMR_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Millis_TMR_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Millis_TMR_Start() routine.
*
*******************************************************************************/
void Millis_TMR_Start(void)
{
    if (0u == Millis_TMR_initVar)
    {
        Millis_TMR_Init();
        Millis_TMR_initVar = 1u;
    }

    Millis_TMR_Enable();
}


/*******************************************************************************
* Function Name: Millis_TMR_Stop
********************************************************************************
*
* Summary:
*  Disables the Millis_TMR.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_BLOCK_CONTROL_REG &= (uint32)~Millis_TMR_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Millis_TMR. This function is used when
*  configured as a generic Millis_TMR and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Millis_TMR to operate in
*   Values:
*   - Millis_TMR_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Millis_TMR_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Millis_TMR_MODE_QUAD - Quadrature decoder
*         - Millis_TMR_MODE_PWM - PWM
*         - Millis_TMR_MODE_PWM_DT - PWM with dead time
*         - Millis_TMR_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_MODE_MASK;
    Millis_TMR_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Millis_TMR_MODE_X1 - Counts on phi 1 rising
*         - Millis_TMR_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Millis_TMR_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_QUAD_MODE_MASK;
    Millis_TMR_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Millis_TMR_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Millis_TMR_PRESCALE_DIVBY2    - Divide by 2
*         - Millis_TMR_PRESCALE_DIVBY4    - Divide by 4
*         - Millis_TMR_PRESCALE_DIVBY8    - Divide by 8
*         - Millis_TMR_PRESCALE_DIVBY16   - Divide by 16
*         - Millis_TMR_PRESCALE_DIVBY32   - Divide by 32
*         - Millis_TMR_PRESCALE_DIVBY64   - Divide by 64
*         - Millis_TMR_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_PRESCALER_MASK;
    Millis_TMR_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Millis_TMR runs
*  continuously or stops when terminal count is reached.  By default the
*  Millis_TMR operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_ONESHOT_MASK;
    Millis_TMR_CONTROL_REG |= ((uint32)((oneShotEnable & Millis_TMR_1BIT_MASK) <<
                                                               Millis_TMR_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPWMMode(uint32 modeMask)
{
    Millis_TMR_TRIG_CONTROL2_REG = (modeMask & Millis_TMR_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Millis_TMR_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_PWM_SYNC_KILL_MASK;
    Millis_TMR_CONTROL_REG |= ((uint32)((syncKillEnable & Millis_TMR_1BIT_MASK)  <<
                                               Millis_TMR_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_PWM_STOP_KILL_MASK;
    Millis_TMR_CONTROL_REG |= ((uint32)((stopOnKillEnable & Millis_TMR_1BIT_MASK)  <<
                                                         Millis_TMR_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_PRESCALER_MASK;
    Millis_TMR_CONTROL_REG |= ((uint32)((deadTime & Millis_TMR_8BIT_MASK) <<
                                                          Millis_TMR_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - Millis_TMR_INVERT_LINE   - Inverts the line output
*         - Millis_TMR_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_INV_OUT_MASK;
    Millis_TMR_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Millis_TMR_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_WriteCounter(uint32 count)
{
    Millis_TMR_COUNTER_REG = (count & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 Millis_TMR_ReadCounter(void)
{
    return (Millis_TMR_COUNTER_REG & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Millis_TMR_COUNT_UP       - Counts up
*     - Millis_TMR_COUNT_DOWN     - Counts down
*     - Millis_TMR_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Millis_TMR_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_UPDOWN_MASK;
    Millis_TMR_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_WritePeriod(uint32 period)
{
    Millis_TMR_PERIOD_REG = (period & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Millis_TMR_ReadPeriod(void)
{
    return (Millis_TMR_PERIOD_REG & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_RELOAD_CC_MASK;
    Millis_TMR_CONTROL_REG |= (swapEnable & Millis_TMR_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_WritePeriodBuf(uint32 periodBuf)
{
    Millis_TMR_PERIOD_BUF_REG = (periodBuf & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Millis_TMR_ReadPeriodBuf(void)
{
    return (Millis_TMR_PERIOD_BUF_REG & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_CONTROL_REG &= (uint32)~Millis_TMR_RELOAD_PERIOD_MASK;
    Millis_TMR_CONTROL_REG |= ((uint32)((swapEnable & Millis_TMR_1BIT_MASK) <<
                                                            Millis_TMR_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Millis_TMR_WriteCompare(uint32 compare)
{
    #if (Millis_TMR_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Millis_TMR_CY_TCPWM_4000) */

    #if (Millis_TMR_CY_TCPWM_4000)
        currentMode = ((Millis_TMR_CONTROL_REG & Millis_TMR_UPDOWN_MASK) >> Millis_TMR_UPDOWN_SHIFT);

        if (((uint32)Millis_TMR__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Millis_TMR__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Millis_TMR_CY_TCPWM_4000) */
    
    Millis_TMR_COMP_CAP_REG = (compare & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Millis_TMR_ReadCompare(void)
{
    #if (Millis_TMR_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Millis_TMR_CY_TCPWM_4000) */

    #if (Millis_TMR_CY_TCPWM_4000)
        currentMode = ((Millis_TMR_CONTROL_REG & Millis_TMR_UPDOWN_MASK) >> Millis_TMR_UPDOWN_SHIFT);
        
        regVal = Millis_TMR_COMP_CAP_REG;
        
        if (((uint32)Millis_TMR__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Millis_TMR__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Millis_TMR_16BIT_MASK);
    #else
        return (Millis_TMR_COMP_CAP_REG & Millis_TMR_16BIT_MASK);
    #endif /* (Millis_TMR_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Millis_TMR_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Millis_TMR_WriteCompareBuf(uint32 compareBuf)
{
    #if (Millis_TMR_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Millis_TMR_CY_TCPWM_4000) */

    #if (Millis_TMR_CY_TCPWM_4000)
        currentMode = ((Millis_TMR_CONTROL_REG & Millis_TMR_UPDOWN_MASK) >> Millis_TMR_UPDOWN_SHIFT);

        if (((uint32)Millis_TMR__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Millis_TMR__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Millis_TMR_CY_TCPWM_4000) */
    
    Millis_TMR_COMP_CAP_BUF_REG = (compareBuf & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Millis_TMR_ReadCompareBuf(void)
{
    #if (Millis_TMR_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Millis_TMR_CY_TCPWM_4000) */

    #if (Millis_TMR_CY_TCPWM_4000)
        currentMode = ((Millis_TMR_CONTROL_REG & Millis_TMR_UPDOWN_MASK) >> Millis_TMR_UPDOWN_SHIFT);

        regVal = Millis_TMR_COMP_CAP_BUF_REG;
        
        if (((uint32)Millis_TMR__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Millis_TMR__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Millis_TMR_16BIT_MASK);
    #else
        return (Millis_TMR_COMP_CAP_BUF_REG & Millis_TMR_16BIT_MASK);
    #endif /* (Millis_TMR_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 Millis_TMR_ReadCapture(void)
{
    return (Millis_TMR_COMP_CAP_REG & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 Millis_TMR_ReadCaptureBuf(void)
{
    return (Millis_TMR_COMP_CAP_BUF_REG & Millis_TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Millis_TMR_TRIG_LEVEL     - Level
*     - Millis_TMR_TRIG_RISING    - Rising edge
*     - Millis_TMR_TRIG_FALLING   - Falling edge
*     - Millis_TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_TRIG_CONTROL1_REG &= (uint32)~Millis_TMR_CAPTURE_MASK;
    Millis_TMR_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Millis_TMR_TRIG_LEVEL     - Level
*     - Millis_TMR_TRIG_RISING    - Rising edge
*     - Millis_TMR_TRIG_FALLING   - Falling edge
*     - Millis_TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_TRIG_CONTROL1_REG &= (uint32)~Millis_TMR_RELOAD_MASK;
    Millis_TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Millis_TMR_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Millis_TMR_TRIG_LEVEL     - Level
*     - Millis_TMR_TRIG_RISING    - Rising edge
*     - Millis_TMR_TRIG_FALLING   - Falling edge
*     - Millis_TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_TRIG_CONTROL1_REG &= (uint32)~Millis_TMR_START_MASK;
    Millis_TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Millis_TMR_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Millis_TMR_TRIG_LEVEL     - Level
*     - Millis_TMR_TRIG_RISING    - Rising edge
*     - Millis_TMR_TRIG_FALLING   - Falling edge
*     - Millis_TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_TRIG_CONTROL1_REG &= (uint32)~Millis_TMR_STOP_MASK;
    Millis_TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Millis_TMR_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Millis_TMR_TRIG_LEVEL     - Level
*     - Millis_TMR_TRIG_RISING    - Rising edge
*     - Millis_TMR_TRIG_FALLING   - Falling edge
*     - Millis_TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_TRIG_CONTROL1_REG &= (uint32)~Millis_TMR_COUNT_MASK;
    Millis_TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Millis_TMR_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - Millis_TMR_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Millis_TMR_CMD_RELOAD     - Trigger Reload/Index command
*     - Millis_TMR_CMD_STOP       - Trigger Stop/Kill command
*     - Millis_TMR_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Millis_TMR_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Millis_TMR_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Millis_TMR.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Millis_TMR_STATUS_DOWN    - Set if counting down
*     - Millis_TMR_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Millis_TMR_ReadStatus(void)
{
    return ((Millis_TMR_STATUS_REG >> Millis_TMR_RUNNING_STATUS_SHIFT) |
            (Millis_TMR_STATUS_REG & Millis_TMR_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Millis_TMR_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Millis_TMR_INTR_MASK_TC       - Terminal count mask
*     - Millis_TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetInterruptMode(uint32 interruptMask)
{
    Millis_TMR_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Millis_TMR_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - Millis_TMR_INTR_MASK_TC       - Terminal count mask
*     - Millis_TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Millis_TMR_GetInterruptSourceMasked(void)
{
    return (Millis_TMR_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Millis_TMR_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - Millis_TMR_INTR_MASK_TC       - Terminal count mask
*     - Millis_TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Millis_TMR_GetInterruptSource(void)
{
    return (Millis_TMR_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Millis_TMR_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Millis_TMR_INTR_MASK_TC       - Terminal count mask
*     - Millis_TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_ClearInterrupt(uint32 interruptMask)
{
    Millis_TMR_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Millis_TMR_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Millis_TMR_INTR_MASK_TC       - Terminal count mask
*     - Millis_TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Millis_TMR_SetInterrupt(uint32 interruptMask)
{
    Millis_TMR_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
