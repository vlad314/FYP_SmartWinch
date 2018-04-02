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


#ifndef MODBUS_REGS_H_
#define MODBUS_REGS_H_


// Slave registers
enum 
{
    Winch_ID, //set via dip_switches
    Soft_Reset, //for emergency stop

    Max_Velocity,       // this is in mm/s used for motion control
    Max_Acceleration,   // this is in mm/s^2 used for motion control

    Target_Setpoint, //for cable length in mm (absolute control)
    Target_Setpoint_Offset, //used for relative control

    //MCP266
    Kp_velocity,
    Ki_velocity,
    Kd_velocity,
    Max_Encoder_Feedrate, //max speed at 100% power in mm/s

    //MCP266
    Kp_position,
    Ki_position,
    Kd_position,

    Kp, //legacy
    Ki, //legacy
    Kd, //legacy
    PID_Setpoint, //for motion planner (read only)

    Target_X,
    Target_Y,
    Target_Z,

    Target_X_Offset,
    Target_Y_Offset,
    Target_Z_Offset,

    Field_Length, //in mm
    Field_Width, //in mm

    Homing_switch, //read only

    Current_Encoder_Count, //in mm
    Current_PWM, //in percent
    Current_RPM,

    Current_X,
    Current_Y,
    Current_Z,

    Current_Length_Winch0,
    Current_Length_Winch1,
    Current_Length_Winch2,
    Current_Length_Winch3,

    Target_Length_Winch0,
    Target_Length_Winch1,
    Target_Length_Winch2,
    Target_Length_Winch3,

    Current_Force_Winch0,
    Current_Force_Winch1,
    Current_Force_Winch2,
    Current_Force_Winch3,

    ADC0,
    ADC1,
    ADC2,
    ADC3,

    Homing_Flag, //obsolete
    Kinematic_mode,
    Sync,

    Follow_Waypoints,
    Current_Waypoints_Pointer,
    Number_of_Waypoints,
    Dwell_Time,

    //start of waypoints
    X1 = 64,
    Y1,
    Z1,
    X2,
    Y2,
    Z2, //etc..

    MB_HREGS  = 2048 
};

extern signed int modbus_holding_regs[MB_HREGS];

#endif /* MODBUS_REGS_H_ */


/* [] END OF FILE */
