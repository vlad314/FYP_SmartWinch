/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

// Slave registers
enum {                         
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
  MB_HREGS                    // Dummy register. using 0 offset to keep size of array
};

int modbus_holding_regs[MB_HREGS];

/* [] END OF FILE */
