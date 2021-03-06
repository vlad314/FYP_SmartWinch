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
* @file nRF24_COMMANDS.c
*
* @brief The nRF24 radio is controlled via commands, this file implement all
* the available commands.
* 
*/

#include "nRF24_CONFIG.h"
#include "nRF24_LL_SPI.h"
#include "nRF24_COMMANDS.h"
#include "nRF24_FUNCS.h"
#include "nRF24_REGS.h"

/**
 * Send a command to the nRF24 radio.
 *
 * @param const nrf_cmd cmd: Command to send to the nRF24 radio.
 */
void nRF24_send_command(const nrf_cmd cmd)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, cmd);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 1) {
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(cmd);

    while (SPI_SpiUartGetRxBufferSize() != 1) {
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(cmd);

    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);
#endif
}

/**
 * @brief Reuse last transmitted payload.
 *
 * Used for a PTX device.
 * Reuse last transmitted payload. TX payload reuse is active until
 * W_TX_PAYLOAD or FLUSH_TX is executed, TX payload reuse must not be
 * activated or deactivated during package transmission.
 */
void nRF24_reuse_tx_payload_cmd(void)
{
    nRF24_send_command(NRF_REUSE_TX_PL_CMD);
}

/**
 * @brief Flush RX FIFO.
 *
 * Used in RX mode.
 * Flush RX FIFO. Should be not executed during transmission of acknowledge,
 * that is, acknowledge package will not be completed.
 */
void nRF24_flush_rx_cmd(void)
{
    nRF24_send_command(NRF_FLUSH_RX_CMD);
}

/**
 * Used in TX mode.
 * Flush TX FIFO.
 */
void nRF24_flush_tx_cmd(void)
{
    nRF24_send_command(NRF_FLUSH_TX_CMD);
}

/**
 * Used in RX mode.
 * Read RX payload: 1 - 32 bytes. A read operation always starts at byte 0.
 * Payload is deleted from FIFO after it is read.
 *
 * @param uint8_t* data:
 * @param const size_t size:
 */
void nRF24_read_rx_payload_cmd(uint8_t* data, const size_t size)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_R_RX_PAYLOAD_CMD);
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 0) {
    }
    
    (void)Cy_SCB_SPI_Read(SPI_HW);
    
    for (size_t i = 0; i < size; i++) {
        Cy_SCB_SPI_Write(SPI_HW, NRF_NOP_CMD);
        while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 0) {
        }
        data[i] = Cy_SCB_SPI_Read(SPI_HW);
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_R_RX_PAYLOAD_CMD);
    while (SPI_SpiUartGetRxBufferSize() == 0){
    }
    // Read the status register, just to clear the rx fifo
    SPI_SpiUartReadRxData();

    for (size_t i = 0; i < size; i++) {
        SPI_SpiUartWriteTxData(NRF_NOP_CMD);
        while (SPI_SpiUartGetRxBufferSize() == 0){
        }
        data[i] = SPI_SpiUartReadRxData();
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_R_RX_PAYLOAD_CMD);

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
 * Write TX payload: 1 - 32 bytes.
 * A write operation always starts at byte 0 used in TX payload.
 *
 * @param const uint8_t* data:
 * @param const size_t size:
 */
void nRF24_write_tx_payload_cmd(const uint8_t* data, const size_t size)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_W_TX_PAYLOAD_CMD);
    Cy_SCB_SPI_WriteArray(SPI_HW, data, size);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != (1 + size)) {
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_W_TX_PAYLOAD_CMD);
    SPI_SpiUartPutArray(data, size);

    while (SPI_SpiUartGetRxBufferSize() != (1 + size)) {
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_W_TX_PAYLOAD_CMD);
    SPI_PutArray(data, size);
    
    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);
#endif
}

/**
 * Read RX payload width for the top R_RX_PAYLOAD in the RX FIFO.
 * Note: Flush RX FIFO if the read value is larger than 32 bytes.
 *
 * @return uint8_t: width of the payload on the top of the RX FIFO.
 */
uint8_t nRF24_read_payload_width_cmd(void)
{
    uint8_t width = 0;
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_R_RX_PL_WID_CMD);
    Cy_SCB_SPI_Write(SPI_HW, NRF_NOP_CMD);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 2) {
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
    
    (void)Cy_SCB_SPI_Read(SPI_HW);
    width = Cy_SCB_SPI_Read(SPI_HW);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_R_RX_PL_WID_CMD);
    SPI_SpiUartWriteTxData(NRF_NOP_CMD);

    while (SPI_SpiUartGetRxBufferSize() != 2) {
    }
    SS_Write(1);

    // This is the STATUS Register
    (void)SPI_SpiUartReadRxData();
    // This is the data we want
    width = SPI_SpiUartReadRxData();
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_R_RX_PL_WID_CMD);
    SPI_WriteTxData(NRF_NOP_CMD);

    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);

    // This is the STATUS Register
    (void)SPI_ReadRxData();
    // This is the data we want
    width = SPI_ReadRxData();
#endif

    // If width is greater than 32 then is garbage, we must flush the RX FIFO
    if (32 < width) {
        nRF24_flush_rx_cmd();
    }

    return width;
}

/**
 * @brief Write Payload to be transmitted together with ACK packet.
 *
 * Used in RX mode.
 * Write Payload to be transmitted together with ACK packet on PIPE PPP
 * (PPP valid in the range from 000 to 101). Maximum three ACK packet
 * payloads can be pending. Payloads with same PPP are handled using
 * first in - first out principle.
 * Write payload: 1 - 32 bytes.
 * A write operation always starts at byte 0.
 *
 * @param const nrf_pipe pipe:
 * @param const uint8_t* data:
 * @param const size_t size:
 */
void nRF24_write_ack_payload_cmd(const nrf_pipe pipe, const uint8_t* data,
                                        const size_t size)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_W_ACK_PAYLOAD_CMD | pipe);
    Cy_SCB_SPI_WriteArray(SPI_HW, data, size);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != (1 + size)) {
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);

    SPI_SpiUartWriteTxData(NRF_W_ACK_PAYLOAD_CMD | pipe);
    SPI_SpiUartPutArray(data, size);

    while (SPI_SpiUartGetRxBufferSize() != (1 + size)) {
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);

    SPI_WriteTxData(NRF_W_ACK_PAYLOAD_CMD | pipe);
    SPI_PutArray(data, size);
    
    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);
#endif
}

/**
 * Used in TX mode.
 * Disable AUTOACK on this packet.
 *
 * @param const uint8_t* data:
 * @param const size_t size:
 */
void nRF24_no_ack_payload_cmd(const uint8_t* data, const size_t size)
{
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_W_TX_PAYLOAD_NOACK_CMD);
    Cy_SCB_SPI_WriteArray(SPI_HW, data, size);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != (1 + size)) {
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);

    SPI_SpiUartWriteTxData(NRF_W_TX_PAYLOAD_NOACK_CMD);
    SPI_SpiUartPutArray(data, size);

    while (SPI_SpiUartGetRxBufferSize() != (1 + size)) {
    }
    SS_Write(1);
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);

    SPI_WriteTxData(NRF_W_TX_PAYLOAD_NOACK_CMD);
    SPI_PutArray(data, size);
    
    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);
#endif
}

/**
 * NOP (No OPeration) Command. Might be used to read the STATUS register.
 *
 * @return uint8_t: STATUS register.
 */
uint8_t nRF24_nop_cmd(void)
{
    uint8_t status = 0;
#if defined(CY_SCB_SPI_H) // SCB Block
#if defined(SPI_CY_SCB_SPI_PDL_H) // PSoC6
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
    
    Cy_SCB_SPI_Write(SPI_HW, NRF_NOP_CMD);
    
    while (Cy_SCB_SPI_GetNumInRxFifo(SPI_HW) != 1) {
    }
    Cy_GPIO_Set(SS_PORT, SS_NUM);
    
    status = Cy_SCB_SPI_Read(SPI_HW);
#else // PSoC4
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();

    SS_Write(0);
    SPI_SpiUartWriteTxData(NRF_NOP_CMD);

    while (SPI_SpiUartGetRxBufferSize() != 1) {
    }
    SS_Write(1);

    status = SPI_SpiUartReadRxData();
#endif
#else // UDB Block
    SPI_ClearRxBuffer();
    SPI_ClearTxBuffer();

    SS_Write(0);
    SPI_WriteTxData(NRF_NOP_CMD);

    while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
    }
    SS_Write(1);

    status = SPI_ReadRxData();
#endif
    return status;
}

/* [] END OF FILE */
