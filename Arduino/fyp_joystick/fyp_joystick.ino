//25th May 2018

#include <ModbusMaster.h>
//#include "ModbusMaster.h"

//#include "ModbusMaster/src/ModbusMaster.h"
#include <PS2X_lib.h>

ModbusMaster node;
PS2X ps2x;

#include "modbus_regs.h"

#define PS2_DAT        11 
#define PS2_CMD        10 
#define PS2_SEL        9  
#define PS2_CLK        8  

#define pressures   true
#define rumble      true

byte vibrate = 0;

void setup()
{
  Serial.begin(115200);
  node.begin(0, Serial);
  pinMode(13, OUTPUT);
  while(ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble) != 0)
  {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
  }
}

int max_array(int *array_1d, int array_size)
{
  int temp = 0;

  for (char i = 0; i < array_size; i++)
  {
    if (temp < array_1d[i])
      temp = array_1d[i];
  }
  return temp;
}


void winches_reset()
{
  node.begin(0, Serial);
  node.setTransmitBuffer(0, 1);
  node.writeMultipleRegisters(Soft_Reset, 1); 
}

//relative control
void jog_winch(int winch_id, int distance)
{
  node.begin(winch_id, Serial);
  node.setTransmitBuffer(0, distance);
  node.writeMultipleRegisters(Target_Setpoint_Offset, 1);  
}

//relative control
void jog_payload(int x, int y, int z)
{
  node.begin(0, Serial);
  node.setTransmitBuffer(0, x/3);
  node.setTransmitBuffer(1, y/3);
  node.setTransmitBuffer(2, z/3);
  node.writeMultipleRegisters(Target_X_Offset, 3);
}


bool safety_flag = 0;
int LX, LY, RX, RY;
int LR[4];

void loop()
{  
  //read controller and set large motor to spin at 'vibrate' speed
  ps2x.read_gamepad(false, vibrate); 
  
  if(ps2x.Button(PSB_START))
  {
    delay(200); //debounce
    safety_flag ^= 1;
  }

  //led blinker
  if (safety_flag)
  {
    static bool led_state;
    static long old;
    if(millis() - old > 200)
    {
      old = millis();
      digitalWrite(13, led_state);
      led_state ^= 1;
    }
  }
  else
    digitalWrite(13, LOW);

  //reset all wiches if L1 and R1 are pressed  
  if(ps2x.Button(PSB_L1) && ps2x.Button(PSB_R1))
    winches_reset();

  //read analog joystick
  LX = (int)ps2x.Analog(PSS_LX) - 128;
  LY = 128 - (int)ps2x.Analog(PSS_LY);
  RX = (int)ps2x.Analog(PSS_RX) - 128;
  RY = 128 - (int)ps2x.Analog(PSS_RY);

  //set the vibration intensity according
  //to maximum analog excursion
  LR[0] = abs(LX);
  LR[1] = abs(LY);
  LR[2] = abs(RX);
  LR[3] = abs(RY);
  vibrate = max_array(LR, 4)>>1;

  //jog control
  if(safety_flag)
  {
    static long old;

    if (ps2x.NewButtonState())
      old = 0;
    
    if (millis() - old > 400)
    {
      old = millis();
      
      int delta_length = 10;
      if(ps2x.Button(PSB_L2))
        delta_length += 20;
      if(ps2x.Button(PSB_R2))
        delta_length += 10;
          
      if(ps2x.Button(PSB_PAD_DOWN))
        jog_winch(1, delta_length);
      if(ps2x.Button(PSB_PAD_LEFT))
        jog_winch(2, delta_length);
      if(ps2x.Button(PSB_PAD_UP))
        jog_winch(3, delta_length);
      if(ps2x.Button(PSB_PAD_RIGHT))
        jog_winch(4, delta_length);
        
      if(ps2x.Button(PSB_CROSS))
        jog_winch(1, -1*delta_length);
      if(ps2x.Button(PSB_SQUARE))
        jog_winch(2, -1*delta_length);
      if(ps2x.Button(PSB_TRIANGLE))
        jog_winch(3, -1*delta_length);
      if(ps2x.Button(PSB_CIRCLE))
        jog_winch(4, -1*delta_length);

      if(vibrate > 0)
        jog_payload(LX, LY, RY);
    }
  }
}
