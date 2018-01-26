/****************************************************************************
* This file is part of the nRF24 Custom Component for PSoC Devices.
*
* Copyright (C) 2017 Carlos Diaz <carlos.santiago.diaz@gmail.com>
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
****************************************************************************/

/**
* @file nRF24_LL_SPI.c
*
* @brief The nRF24 radio is controlled via SPI, this file have all the SPI
* communication between the PSoC and the nRF24 radio.
*/

#include "nRF24_CONFIG.h"
#include "nRF24_LL_SPI.h"

/**
 * Read a (1 byte long) nRF24 register.
 *
 * @param const nrf_register reg: Register to be read.
 *
 * @return uint8_t: Content of the register.
 */
uint8_t nRF24_read_register(const nrf_register reg)
{
    uint8_t data = 0;
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_R_REGISTER_CMD | reg);
    Cy_SCB_SPI_Write(SPI_HW, NRF_NOP_CMD);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 2) {
    }
    
    Cy_GPIO_Set(SS_PORT, SS_NUM);
    
    (void)Cy_SCB_SPI_Read(SPI_HW);
    data = Cy_SCB_SPI_Read(SPI_HW);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_R_REGISTER_CMD | reg);
    SPI_SpiUartWriteTxData(NRF_NOP_CMD);

    while (SPI_SpiUartGetRxBufferSize() != 2) {
    }
    SS_Write(1);

    // This is the STATUS Register
    (void)SPI_SpiUartReadRxData();
    // This is the data we want
    data = SPI_SpiUartReadRxData();
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_R_REGISTER_CMD | reg);
    SPI_WriteTxData(NRF_NOP_CMD);

    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);

    // This is the STATUS Register
    (void)SPI_ReadRxData();
    // This is the data we want
    data = SPI_ReadRxData();
#endif
    return data;
}

/**
 * Read a (multi byte long) nRF24 register.
 *
 * @param const nrf_register reg: Register to be read.
 * @param uint8_t* data: Pointer to where the content of the register
 * will be stored.
 * @param size_t size: Size of the register, larger register hold 5 bytes of
 * data.
 */
void nRF24_read_long_register(const nrf_register reg, uint8_t* data,
                                       const size_t size)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    Cy_SCB_SPI_Write(SPI_HW, NRF_R_REGISTER_CMD | reg);
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) == 0) {
    }
    
    (void)Cy_SCB_SPI_Read(SPI_HW);
    for(size_t i = 0; i < size; i++){
        Cy_SCB_SPI_Write(SPI_HW, NRF_NOP_CMD);
        while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) == 0) {}
        data[1] = Cy_SCB_SPI_Read(SPI_HW);
    }
    
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_R_REGISTER_CMD | reg);
    while (SPI_SpiUartGetRxBufferSize() == 0){
    }
    
    // Read the status register, just to clear the rx fifo
    SPI_SpiUartReadRxData();
    //SPI_SpiUartClearRxBuffer();
    
    for (size_t i = 0; i < size; i++) {
        SPI_SpiUartWriteTxData(NRF_NOP_CMD);
        while (SPI_SpiUartGetRxBufferSize() == 0){}
        data[i] = SPI_SpiUartReadRxData();
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearFIFO();

    SS_Write(0);
    SPI_WriteTxData(NRF_R_REGISTER_CMD | reg);
    // Wait for the byte to be sent
    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    // Read the status register, just to clear the rx fifo
    SPI_ReadRxData();
    
    for (size_t i = 0; i < size; i++) {
        SPI_WriteTxData(NRF_NOP_CMD);
        while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
        }
        data[i] = SPI_ReadRxData();
    }

    SS_Write(1);
#endif
}

/**
 * Write one byte to a nRF24 Register.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t data: Data to be written into the register.
 */
void nRF24_write_register(const nrf_register reg, const uint8_t data)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    Cy_SCB_SPI_Write(SPI_HW, NRF_W_REGISTER_CMD | reg);
    Cy_SCB_SPI_Write(SPI_HW, data);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 2) {
    }
    
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_W_REGISTER_CMD | reg);
    SPI_SpiUartWriteTxData(data);

    while (SPI_SpiUartGetRxBufferSize() != 2) {
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_W_REGISTER_CMD | reg);
    SPI_WriteTxData(data);

    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);
#endif
}

/**
 * Write one or more bytes to a nRF24 Register, larger register is 5 bytes.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t* data: Data to write into the register.
 * @param size_t size: Size (in bytes) of the data to be written.
 */
void nRF24_write_long_register(const nrf_register reg, const uint8_t* data,
                                        const size_t size)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    Cy_SCB_SPI_Write(SPI_HW, NRF_W_REGISTER_CMD | reg);
    Cy_SCB_SPI_WriteArray(SPI_HW, data, size);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != (1 + size)) {
    }
    
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);

    SPI_SpiUartWriteTxData(NRF_W_REGISTER_CMD | reg);
    SPI_SpiUartPutArray(data, size);

    // we're not using the embedded SS pin on the SCB component, can't use the
    // SPI_Status function, we have to count the bytes on the RxBuffer to know
    // when the transition is done, size + 1 bytes == W_REGISTER_CMD + data
    while (SPI_SpiUartGetRxBufferSize() != (1 + size)) {
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_W_REGISTER_CMD | reg);
    SPI_PutArray(data, size);

    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);
#endif
}

/**
 * Read a bit of a nrf_register.
 *
 * @param const nrf_register reg: Register to be read.
 * @param uint8_t bit: Bit to be read.
 *
 * @return bool: Return 1 if bit is set (logic 1), return 0 if the bit
 * is clear (logic 0).
 */
bool nRF24_read_bit(const nrf_register reg, const uint8_t bit)
{
    return (nRF24_read_register(reg) & (1 << bit)) != 0;
}

/**
 * Set (logic 1) or clear (logic 0) a given bit of a given nRF24 register.
 *
 * Before setting the value we want to write to the bit we first check it's value,
 * if the bit have the value we wanted already, we exit the function early.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t bit: Position of the bit to be written.
 * @param const bool value: Value (Logic 1 or 0) to write into the bit.
 */
void nRF24_write_bit(const nrf_register reg, const uint8_t bit,
                               const bool value)
{
    uint8_t temp = nRF24_read_register(reg);

    // Check if the bit of interest is set
    if ((temp & (1 << bit)) != 0) {
        // Return if we wanted to set it, continue if we wanted to clear it.
        if (value) {
            return;
        }
    } else { // the bit is clear
        if (!value) {
            return; // return if we wanted to clear the bit
        }
    }

    // Calculate the new value to be written in the register
    temp = value ? temp | (1 << bit) : temp & ~(1 << bit);

    nRF24_write_register(reg, temp);
}

/**
 * Clear (set to 0) a given bit of a given nRF24 register.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t bit: Bit to be written.
 */
void nRF24_clear_bit(const nrf_register reg, const uint8_t bit)
{
    nRF24_write_bit(reg, bit, 0);
}

/**
 * Set (set to 1) a given bit of a given nRF24 register.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t bit: Bit to be written.
 */
void nRF24_set_bit(const nrf_register reg, const uint8_t bit)
{
    nRF24_write_bit(reg, bit, 1);
}

/* [] END OF FILE */
