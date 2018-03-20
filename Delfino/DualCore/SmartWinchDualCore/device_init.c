/*
 * device_init.c
 *
 *  Created on: 10 Feb 2018
 *      Author: AfdhalAtiffTan
 */


#include "device_init.h"

void init_gpio()
{
    //////////////////////////////////////////////
    //<for on-board LEDs>
    //set pin12 and pin13 as gpio
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);

    //set gpio12 and gpio13 as pushpullOut
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);

    //turn off both led (active-low)
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);

    //set both pins as output
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    //////////////////////////////////////////////
    //<for setting winchID via 2-bit dip-switches>
    //set pin61 and pin123 as gpio
    GPIO_setPinConfig(DEVICE_GPIO_CFG_ID0);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_ID1);

    //set pull up on gpio61 and gpio123
    GPIO_setPadConfig(DEVICE_GPIO_PIN_ID0, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_ID1, GPIO_PIN_TYPE_PULLUP);

    //set both pins as input
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_ID0, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_ID1, GPIO_DIR_MODE_IN);

    //////////////////////////////////////////////
    //<for debug mode switche>
    //set pin61 and pin123 as gpio
    GPIO_setPinConfig(DEVICE_GPIO_CFG_DBG);

    //set pull up on gpio61 and gpio123
    GPIO_setPadConfig(DEVICE_GPIO_PIN_DBG, GPIO_PIN_TYPE_PULLUP);

    //set both pins as input
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_DBG, GPIO_DIR_MODE_IN);
}

void init_uart_A()
{
    // GPIO28 is the SCI Rx pin.
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    // GPIO29 is the SCI Tx pin.
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    // Initialize SCIA and its FIFO.
    SCI_performSoftwareReset(SCIA_BASE);

    // Configure SCIA for echoback.
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 9600, (  SCI_CONFIG_WLEN_8 |
                                                            SCI_CONFIG_STOP_ONE |
                                                            SCI_CONFIG_PAR_NONE));
    SCI_enableFIFO(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);

    SCI_resetChannels(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);

    //
    // RX and TX FIFO Interrupts Enabled
    //
    SCI_enableInterrupt(SCIA_BASE, (SCI_INT_RXFF | SCI_INT_TXFF));
    SCI_disableInterrupt(SCIA_BASE, SCI_INT_RXERR);

    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);
    SCI_performSoftwareReset(SCIA_BASE);

    Interrupt_enable(INT_SCIA_RX);
    //Interrupt_enable(INT_SCIA_TX);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);



    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_SCIA_RX, sciaRXFIFOISR);
    Interrupt_register(INT_SCIA_TX, sciaTXFIFOISR);
}

void init_uart_B()
{
    //SCI Rx pin.
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDB, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDB);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDB, GPIO_PIN_TYPE_PULLUP); //pullup, to allow multidrop
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDB, GPIO_QUAL_ASYNC);

    //SCI Tx pin.
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDB, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDB);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDB, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDB, GPIO_PIN_TYPE_OD); //open drain output, to allow multidrop
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDB, GPIO_QUAL_ASYNC);

    // Initialize SCIB and its FIFO.
    SCI_performSoftwareReset(SCIB_BASE);

    // Configure SCIB for echoback.
    SCI_setConfig(SCIB_BASE, DEVICE_LSPCLK_FREQ, 9600, (  SCI_CONFIG_WLEN_8 |
                                                            SCI_CONFIG_STOP_ONE |
                                                            SCI_CONFIG_PAR_NONE));
    SCI_enableFIFO(SCIB_BASE);
    SCI_resetRxFIFO(SCIB_BASE);
    SCI_resetTxFIFO(SCIB_BASE);

    SCI_resetChannels(SCIB_BASE);
    SCI_clearInterruptStatus(SCIB_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableModule(SCIB_BASE);
    SCI_performSoftwareReset(SCIB_BASE);

    //
    // RX and TX FIFO Interrupts Enabled
    //
    SCI_enableInterrupt(SCIB_BASE, (SCI_INT_RXFF | SCI_INT_TXFF));
    SCI_disableInterrupt(SCIB_BASE, SCI_INT_RXERR);

    SCI_setFIFOInterruptLevel(SCIB_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);
    SCI_performSoftwareReset(SCIB_BASE);

    Interrupt_enable(INT_SCIB_RX);
    //Interrupt_enable(INT_SCIB_TX);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);



    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_SCIB_RX, scibRXFIFOISR);
    Interrupt_register(INT_SCIB_TX, scibTXFIFOISR);
}

void init_eqep()
{
    //set as eqep
    GPIO_setPinConfig(DEVICE_GPIO_CFG_EQEP1A);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_EQEP1B);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_EQEP1I);

    //set HiZin (because the board already has pull-up resistors and an input buffer)
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EQEP1A, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EQEP1B, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EQEP1I, GPIO_PIN_TYPE_STD);

    //set both pins as input (maybe not needed?)
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_EQEP1A, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_EQEP1B, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_EQEP1I, GPIO_DIR_MODE_IN);


    //
    // Configure the decoder for quadrature count mode
    //
    EQEP_setDecoderConfig(EQEP1_BASE, (EQEP_CONFIG_2X_RESOLUTION |
                                       EQEP_CONFIG_QUADRATURE |
                                       EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(EQEP1_BASE, EQEP_EMULATIONMODE_RUNFREE);

    //
    // Configure the position counter to reset on an index event
    //
    EQEP_setPositionCounterConfig(EQEP1_BASE, EQEP_POSITION_RESET_IDX,
                                  0xFFFFFFFF);

    //
    // Enable the unit timer, setting the frequency to 100 Hz
    //
    EQEP_enableUnitTimer(EQEP1_BASE, (DEVICE_SYSCLK_FREQ / 100));

    //
    // Configure the position counter to be latched on a unit time out
    //
    EQEP_setLatchMode(EQEP1_BASE, EQEP_LATCH_UNIT_TIME_OUT);

    //
    // Enable the eQEP1 module
    //
    EQEP_enableModule(EQEP1_BASE);

    //
    // Configure and enable the edge-capture unit. The capture clock divider is
    // SYSCLKOUT/128. The unit-position event divider is QCLK/32.
    //
    //128 because it is the slowest posible, i.e. 20MHz/128
    //32 because 32count per rotation
    EQEP_setCaptureConfig(EQEP1_BASE, EQEP_CAPTURE_CLK_DIV_128,
                          EQEP_UNIT_POS_EVNT_DIV_8);

    EQEP_enableCapture(EQEP1_BASE);

    //set reset position
    EQEP_setInitialPosition(EQEP1_BASE, 0x80000000);
    EQEP_setPosition(EQEP1_BASE, 0x80000000);

    //enable index reset
    EQEP_setPositionInitMode(EQEP1_BASE, EQEP_INIT_FALLING_INDEX);
}

void init_pwm()
{
    //frequency of pwm is 200MHz/2(internal_divider)/2(updown_cnt)/0xffff = 769Hz

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM2_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO); //may need optimisation (sync)
    EPWM_setADCTriggerEventPrescale(EPWM2_BASE, EPWM_SOC_A, 1); //may need optimisation if hifreq pwm is used

    //
    // Enabling SOCA (start-of-conversion)
    //
    EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);



    //
    // Clear Compare values
    //
    EPWM_setCounterCompareValue(EPWM2_BASE,
                                EPWM_COUNTER_COMPARE_A,
                                0);
    EPWM_setCounterCompareValue(EPWM2_BASE,
                                EPWM_COUNTER_COMPARE_B,
                                0);


    GPIO_setPinConfig(DEVICE_GPIO_CFG_EPWM2A);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_EPWM2B);

    GPIO_setPadConfig(DEVICE_GPIO_PIN_EPWM2A, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EPWM2B, GPIO_PIN_TYPE_STD);

    GPIO_writePin(DEVICE_GPIO_PIN_EPWM2A, 0);
    GPIO_writePin(DEVICE_GPIO_PIN_EPWM2B, 0);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_EPWM2A, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_EPWM2B, GPIO_DIR_MODE_OUT);


    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(EPWM2_BASE, 0xffff);
    EPWM_setPhaseShift(EPWM2_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);


    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(EPWM2_BASE);
    EPWM_setClockPrescaler(EPWM2_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(EPWM2_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    EPWM_setCounterCompareShadowLoadMode(EPWM2_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(EPWM2_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


    //
    // Setting up high resolution pwm
    //
    HRPWM_setMEPControlMode(EPWM2_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setMEPControlMode(EPWM2_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setMEPEdgeSelect(EPWM2_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_EDGE);
    HRPWM_setMEPEdgeSelect(EPWM2_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_EDGE);
    HRPWM_setMEPStep(EPWM2_BASE, 0xff);



    //
    // Assign the interrupt service routines to ePWM interrupt
    //
    Interrupt_register(INT_EPWM2, &epwm2ISR);


    //
    // Enable ePWM interrupts
    //
    Interrupt_enable(INT_EPWM2);


    //
    // Interrupt where we will change the Compare Values
    // Select INT on Time base counter zero event,
    // Enable INT, generate INT on 8th event
    //
    EPWM_setInterruptSource(EPWM2_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM2_BASE);
    EPWM_setInterruptEventCount(EPWM2_BASE, 8U); /* 763/8 = 95Hz interrupt */
}

void init_adc()
{
    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCD_BASE, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode (see #defines above) and load
    // corresponding trims.
    //
    ADC_setMode(ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCD_BASE, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCD_BASE);
    DEVICE_DELAY_US(1000);

    //
    // Configure SOC of ADCD to convert pins on J21. The EPWM2SOCA signal will be
    // the trigger.
    //
    // For 12-bit resolution, a sampling window of 15 (75 ns at a 200MHz
    // SYSCLK rate) will be used.  For 16-bit resolution, a sampling window of
    // 64 (320 ns at a 200MHz SYSCLK rate) will be used.
    //
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM2_SOCA, ADC_CH_ADCIN0, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM2_SOCA, ADC_CH_ADCIN1, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM2_SOCA, ADC_CH_ADCIN2, 15);
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM2_SOCA, ADC_CH_ADCIN3, 15);



    //
    // Set SOC to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER2);
    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER3);

    ADC_enableInterrupt(ADCD_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);
}

void init_timer()
{
    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 40000 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 39999); //should give 200us per tick (overflowed @ 9.9 days) - assuming SYSCLKOUT = 200MHz

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);

    //
    // Initializes timer control register.
    //
    CPUTimer_setEmulationMode(CPUTIMER0_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);

    //
    // Starts CPU-Timer 0
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);
}

void init_smartwinch()
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //self-explanatory
    init_gpio();
    init_uart_A(); //usb uart
    init_uart_B(); //Jumper1 uart
    init_eqep();
    init_pwm();
    init_adc();
    init_timer();
    modbusRTU_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;
}
