//taken from https://os.mbed.com/components/Cypress-FM25W256-256Kb-Wide-Voltage-SPI-/
//ported to C by Afdhal on 20th May 2018

/* Cypress FM25W256 F-RAM component library
 *
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *  *
 *  @author  Toyomasa Watarai
 *  @version 1.0
 *  @date    5-March-2016
 *
 *  http://www.cypress.com/products/nonvolatile-ram
 *  http://www.cypress.com/documentation/datasheets/fm25w256-256-kbit-32-k-8-serial-spi-f-ram?source=search&keywords=FM25W256&cat=technical_documents
 *
 */
 
#include "includes.h"

#ifndef __FM25W256_HEAD__
#define __FM25W256_HEAD__

#define CMD_WREN   0x06
#define CMD_WRDI   0x04
#define CMD_RDSR   0x05
#define CMD_WRSR   0x01
#define CMD_READ   0x03
#define CMD_WRITE  0x02

//#define FM25W256_CLK (20000000) // SPI clock 20MHz

/** An interface for the Cypress 32k byte FM25W256 F-RAM over SPI
 * 
 * @code
 * #include "mbed.h"
 * #include "FM25W256.h"
 * 
 * Serial pc(USBTX, USBRX);
 * FM25W256 f_ram(dp2, dp1, dp6, dp18);
 * 
 * int main()
 * {
 *     uint16_t buf[16];
 *     // Fill buffer
 *     for(int i=0; i<16; i++) {
 *         buf[i] = i;
 *     }
 *     // Write data to F-RAM
 *     f_ram.write(0, buf, 16);
 * 
 *     // Read data from F-RAM
 *     uint16_t adrs = 0;
 *     for(int i=0; i<16; i++) {
 *         pc.printf("0x%04X : ", i * 16);
 *         for(int j=0; j<16; j++) {
 *             pc.printf("%02X ", f_ram.read(adrs++));
 *         }
 *         pc.printf("\n");
 *     }
 *     
 *     while(1) {
 *     }
 * }
 * @endcode
 */
//class FM25W256 {
//public:

    typedef enum  {
        BANK_NONE = 0,
        BANK_UPPER_QUARTER = 1,
        BANK_UPPER_HALF = 2,
        BANK_ALL = 3
    } E_WP;
    
/** Create an interface
 *
 * @param mosi  SPI master-out-slave-in
 * @param miso  SPI master-in-slave-out
 * @param clk   SPI clock
 * @param cs    chip select pin - any free Digital pin will do
 */
    //FM25W256(PinName mosi, PinName miso, PinName clk, PinName cs);

/** Create an interface
 *
 * @param &spi  SPI instance
 * @param cs    chip select pin - any free Digital pin will do
 */
    //FM25W256(SPI &spi, PinName cs);
    
/** write a byte to F-RAM
 * @param address    The address F-RAM to write to
 * @param data       The byte to write there
 */
    void FM25W256_write(uint16_t address, uint16_t data);

/** write multiple bytes to F-RAM from a buffer
 * @param address    The F-RAM address write to
 * @param data       The buffer to write from
 * @param size       The number of bytes to write
 */
    void FM25W256_write_multiple(uint16_t address, uint16_t *data, uint16_t size);

/** read a byte from F-RAM
 * @param address    The address to read from
 * @return the character at that address
 */
    uint16_t FM25W256_read(uint16_t address);

/** read multiple bytes from F-RAM into a buffer
 * @param address    The F-RAM address to read from
 * @param data       The buffer to read into (must be big enough!)
 * @param size       The number of bytes to read
 */
    void FM25W256_read_multiple(uint16_t address, uint16_t *data, uint16_t size);

/** write a byte to the status register
 * @param data  The byte to write the register
 */
    void FM25W256_write_status(uint16_t data);

/** read a byte from the status register
 * @return the character at the register
 */
    uint16_t FM25W256_read_status();

/** Set write protect mode
 * @param bp   E_WP enum value
 */
    void FM25W256_set_write_protect(E_WP bp);

/** Set write protect to non-protect mode
 */
    void FM25W256_clear_write_protect();

// protected:
//     SPI _spi;
//     DigitalOut _cs;
// };

#endif
