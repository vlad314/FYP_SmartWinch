//this library was downloaded from https://github.com/4-20ma/ModbusMaster
//ported to C by Afdhal on 20th May 2018.

/**
@file
Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol).

@defgroup setup ModbusMaster Object Instantiation/Initialization
@defgroup buffer ModbusMaster Buffer Management
@defgroup discrete Modbus Function Codes for Discrete Coils/Inputs
@defgroup register Modbus Function Codes for Holding/Input Registers
@defgroup constant Modbus Function Codes, Exception Codes
*/
/*

  ModbusMaster.h - Arduino library for communicating with Modbus slaves
  over RS232/485 (via RTU protocol).

  Library:: ModbusMaster

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

  
#ifndef ModbusMaster_h
#define ModbusMaster_h


/**
@def __MODBUSMASTER_DEBUG__ (0)
Set to 1 to enable debugging features within class:
  - PIN A cycles for each byte read in the Modbus response
  - PIN B cycles for each millisecond timeout during the Modbus response
*/
#define __MODBUSMASTER_DEBUG__ (0)
#define __MODBUSMASTER_DEBUG_PIN_A__ 4
#define __MODBUSMASTER_DEBUG_PIN_B__ 5

#include "includes.h"

/* _____UTILITY MACROS_______________________________________________________ */


/* _____PROJECT INCLUDES_____________________________________________________ */
// functions to calculate Modbus Application Data Unit CRC
//#include "util/crc16.h"

// functions to manipulate words
//#include "util/word.h"


/* _____CLASS DEFINITIONS____________________________________________________ */
/**
Arduino class library for communicating with Modbus slaves over 
RS232/485 (via RTU protocol).
*/

    //void ModbusMaster_init();

    void ModbusMaster_change_slave(uint16_t slave);
   
    //void ModbusMaster_begin(uint16_t, Stream &serial);
    void ModbusMaster_begin(uint16_t);
    void ModbusMaster_idle(void (*)());
    void ModbusMaster_preTransmission(void (*)());
    void ModbusMaster_postTransmission(void (*)());

    // Modbus exception codes
    /**
    Modbus protocol illegal function exception.
    
    The function code received in the query is not an allowable action for
    the server (or slave). This may be because the function code is only
    applicable to newer devices, and was not implemented in the unit
    selected. It could also indicate that the server (or slave) is in the
    wrong state to process a request of this type, for example because it is
    unconfigured and is being asked to return register values.
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBIllegalFunction            = 0x01;

    /**
    Modbus protocol illegal data address exception.
    
    The data address received in the query is not an allowable address for 
    the server (or slave). More specifically, the combination of reference 
    number and transfer length is invalid. For a controller with 100 
    registers, the ADU addresses the first register as 0, and the last one 
    as 99. If a request is submitted with a starting register address of 96 
    and a quantity of registers of 4, then this request will successfully 
    operate (address-wise at least) on registers 96, 97, 98, 99. If a 
    request is submitted with a starting register address of 96 and a 
    quantity of registers of 5, then this request will fail with Exception 
    Code 0x02 "Illegal Data Address" since it attempts to operate on 
    registers 96, 97, 98, 99 and 100, and there is no register with address 
    100. 
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBIllegalDataAddress         = 0x02;
    
    /**
    Modbus protocol illegal data value exception.
    
    A value contained in the query data field is not an allowable value for 
    server (or slave). This indicates a fault in the structure of the 
    remainder of a complex request, such as that the implied length is 
    incorrect. It specifically does NOT mean that a data item submitted for 
    storage in a register has a value outside the expectation of the 
    application program, since the MODBUS protocol is unaware of the 
    significance of any particular value of any particular register.
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBIllegalDataValue           = 0x03;
    
    /**
    Modbus protocol slave device failure exception.
    
    An unrecoverable error occurred while the server (or slave) was
    attempting to perform the requested action.
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBSlaveDeviceFailure         = 0x04;

    // Class-defined success/exception codes
    /**
    ModbusMaster success.
    
    Modbus transaction was successful; the following checks were valid:
      - slave ID
      - function code
      - response code
      - data
      - CRC
      
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBSuccess                    = 0x00;
    
    /**
    ModbusMaster invalid response slave ID exception.
    
    The slave ID in the response does not match that of the request.
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBInvalidSlaveID             = 0xE0;
    
    /**
    ModbusMaster invalid response function exception.
    
    The function code in the response does not match that of the request.
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBInvalidFunction            = 0xE1;
    
    /**
    ModbusMaster response timed out exception.
    
    The entire response was not received within the timeout period, 
    ModbusMaster::ku8MBResponseTimeout. 
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBResponseTimedOut           = 0xE2;
    
    /**
    ModbusMaster invalid response CRC exception.
    
    The CRC in the response does not match the one calculated.
    
    @ingroup constant
    */
    static const uint16_t ModbusMaster_ku8MBInvalidCRC                 = 0xE3;
    
    uint16_t ModbusMaster_getResponseBuffer(uint16_t);
    void     ModbusMaster_clearResponseBuffer();
    uint16_t  ModbusMaster_setTransmitBuffer(uint16_t, uint16_t);
    void     ModbusMaster_clearTransmitBuffer();
    
    void ModbusMaster_beginTransmission(uint16_t);
    uint16_t ModbusMaster_requestFrom(uint16_t, uint16_t);
    void ModbusMaster_sendBit(bool);
    // void ModbusMaster_send(uint16_t); 
    void ModbusMaster_send(uint16_t);
    // void ModbusMaster_send(uint32_t);
    uint16_t ModbusMaster_available(void);
    uint16_t ModbusMaster_receive(void);
    
    
    uint16_t  ModbusMaster_readCoils(uint16_t, uint16_t);
    uint16_t  ModbusMaster_readDiscreteInputs(uint16_t, uint16_t);
    uint16_t  ModbusMaster_readHoldingRegisters(uint16_t, uint16_t);
    uint16_t  ModbusMaster_readInputRegisters(uint16_t, uint16_t);
    uint16_t  ModbusMaster_writeSingleCoil(uint16_t, uint16_t);
    uint16_t  ModbusMaster_writeSingleRegister(uint16_t, uint16_t);
    uint16_t  ModbusMaster_writeMultipleCoils(uint16_t, uint16_t);
    //uint16_t  ModbusMaster_writeMultipleCoils();
    uint16_t  ModbusMaster_writeMultipleRegisters(uint16_t, uint16_t);
    //uint16_t  ModbusMaster_writeMultipleRegisters();
    uint16_t  ModbusMaster_maskWriteRegister(uint16_t, uint16_t, uint16_t);
    uint16_t  ModbusMaster_readWriteMultipleRegisters(uint16_t, uint16_t, uint16_t, uint16_t);
    //uint16_t  ModbusMaster_readWriteMultipleRegisters(uint16_t, uint16_t);
    


#endif

/**
@example examples/Basic/Basic.pde
@example examples/PhoenixContact_nanoLC/PhoenixContact_nanoLC.pde
@example examples/RS485_HalfDuplex/RS485_HalfDuplex.ino
*/
