/*
 * File:   nRF24_Adapter.c
 * Author: Afdhal Tan
 *
 * Created on 17 December 2017, 22:32
 */

#include "nRF24_Adapter.h"

volatile nrf_irq nRF24_Adapter_Flags;

CY_ISR(nRF24_ISR)
{        
    nRF24_Adapter_Flags = nRF24_get_irq_flag();
    
    LED_Write(~LED_Read());    
    
    //clear flags before exiting isr
    nRF24_clear_all_irqs();
    NRF_IRQ_ClearInterrupt();
    NRF_ISR_ClearPending();
}



/*******************************************************************************
* Function Name: nRF24_Adapter_Start
****************************************************************************//**
*
* \brief Enable interrupt requests from an nRF24 module
*
* More detailed explanation should be here.
*
* <b>Note</b> Don't forget to enable at least one interrupt in the nRF24 module.
*
* \param value
*  None
*
* \return 
*  None 
*
* \sideeffect
*  None known.
*******************************************************************************/
void nRF24_Adapter_Start()
{
    NRF_ISR_StartEx(nRF24_ISR);
    nRF24_start();
}

/* [] END OF FILE */
