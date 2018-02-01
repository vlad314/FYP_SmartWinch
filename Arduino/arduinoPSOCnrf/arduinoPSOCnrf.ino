#include <ModbusSlave232.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Slave registers
enum 
{                         
    Kp,
    Ki,
    Kd,
    PID_Setpoint,
    Current_Encoder_Position, 
    Current_PWM,
    Reset_Source,
    Soft_Reset,  
    CurrSense_A,
    CurrSense_B, 
    PID_Setpoint1,  
    Current_X,
    Current_Y,        
    MB_HREGS                    // Dummy register. using 0 offset to keep size of array
};

int modbus_holding_regs[MB_HREGS];


RF24 radio(7,8);
enum{M2A, A2B};
const uint64_t pipes[] = {0x41324d293aLL, 0x423241293aLL};

ModbusSlave232 mbs;

void setup() {

  // Modbus slave configuration parameters
  // SlaveId 
  const unsigned char SLAVE = 1;
  // Baud rate   
  const long BAUD = 115200;            
  const unsigned PARITY = 'n';

  // Configure msb with config settings
  mbs.configure(SLAVE, BAUD, PARITY );
  
  radio.begin();
  radio.stopListening();
  
  radio.setRetries(2,8);
  radio.setPayloadSize(4);
  radio.setChannel(120);
  radio.setCRCLength(RF24_CRC_16);
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.powerUp();  
  radio.openReadingPipe(0,pipes[A2B]);
  radio.openWritingPipe(pipes[M2A]);   
}

byte x[4] = {0,0,0,0};
int wait = 30;
void loop()
{
  if(mbs.update(modbus_holding_regs, MB_HREGS)>4)
  {
      if(mbs.modbusRTU_Written == 1)
      {                   
          if((mbs.modbusRTU_written_register_flags)&(1<<Kp))
          {
              x[0] = Kp;
              x[1] = modbus_holding_regs[Kp]>>8; //msb
              x[2] = modbus_holding_regs[Kp]&0xff; //lsb
              x[3] = 0;
              mbs.modbusRTU_written_register_flags &= ~(1<<Kp);              
          }
          else if((mbs.modbusRTU_written_register_flags)&(1<<Ki))
          {
              x[0] = Ki;
              x[1] = modbus_holding_regs[Ki]>>8; //msb
              x[2] = modbus_holding_regs[Ki]&0xff; //lsb
              x[3] = 0;
              mbs.modbusRTU_written_register_flags &= ~(1<<Ki);
          }
          else if((mbs.modbusRTU_written_register_flags)&(1<<Kd))
          {
              x[0] = Kd;
              x[1] = modbus_holding_regs[Kd]>>8; //msb
              x[2] = modbus_holding_regs[Kd]&0xff; //lsb
              x[3] = 0;
              mbs.modbusRTU_written_register_flags &= ~(1<<Kd);
          }
          else if((mbs.modbusRTU_written_register_flags)&(1<<PID_Setpoint))
          {
              x[0] = PID_Setpoint;
              x[1] = modbus_holding_regs[PID_Setpoint]>>8; //msb
              x[2] = modbus_holding_regs[PID_Setpoint]&0xff; //lsb
              x[3] = 0;
              mbs.modbusRTU_written_register_flags &= ~(1<<PID_Setpoint);
          }
          else if((mbs.modbusRTU_written_register_flags)&(1<<PID_Setpoint1))
          {
              x[0] = PID_Setpoint1;
              x[1] = modbus_holding_regs[PID_Setpoint1]>>8; //msb
              x[2] = modbus_holding_regs[PID_Setpoint1]&0xff; //lsb
              x[3] = 0;
              mbs.modbusRTU_written_register_flags &= ~(1<<PID_Setpoint1);
          }
          
          else if((mbs.modbusRTU_written_register_flags)&(1<<Soft_Reset))
          {
              x[0] = Soft_Reset;
              x[1] = modbus_holding_regs[Soft_Reset]>>8; //msb
              x[2] = modbus_holding_regs[Soft_Reset]&0xff; //lsb
              x[3] = 0;
              mbs.modbusRTU_written_register_flags &= ~(1<<Soft_Reset);
          } 

          radio.startWrite(x, 4);  

          if((mbs.modbusRTU_written_register_flags&0x00000407) == 0)
                mbs.modbusRTU_Written = 0;    
      }
  }     
}

//void loop1() {  
//  radio.openWritingPipe(pipes[A2B]);
//  radio.startWrite(x[2]++, 4);  
//  delay(500);
//
//  radio.openWritingPipe(pipes[M2A]);
//  radio.startWrite(x[2]++, 4);  
//  delay(500);
//}
