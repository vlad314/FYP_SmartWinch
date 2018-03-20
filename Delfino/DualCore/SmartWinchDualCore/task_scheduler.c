/*
 * task_scheduler.c
 *
 *  Created on: 17 Mar 2018
 *      Author: AfdhalAtiffTan
 */

#include "task_scheduler.h"

void simple_homing_routine()
{
    static length4_struct homed_cable_lengths;

    if(modbus_holding_regs[Homing_Flag] != 0) //if force_homing triggered
    {
        modbus_holding_regs[Homing_Flag] = 0; //acknowledge request

        modbus_holding_regs[Target_X] = 0;
        modbus_holding_regs[Target_Y] = 0;
        modbus_holding_regs[Target_Z] = 0;

        modbus_holding_regs[Current_X] = 0;
        modbus_holding_regs[Current_Y] = 0;
        modbus_holding_regs[Current_Z] = 0;

        homed_cable_lengths = XYZ_to_length4(  	(float) modbus_holding_regs[0], //assuming homed position is at <0, 0, 0>
                                                (float) modbus_holding_regs[0], 
                                                (float) modbus_holding_regs[0], 
                                                (float) modbus_holding_regs[Field_Length]);

        modbus_holding_regs[Target_Length_Winch0] = homed_cable_lengths.lengtha;
        modbus_holding_regs[Target_Length_Winch1] = homed_cable_lengths.lengthb;
        modbus_holding_regs[Target_Length_Winch2] = homed_cable_lengths.lengthc;
        modbus_holding_regs[Target_Length_Winch3] = homed_cable_lengths.lengthd;

        modbus_holding_regs[Current_Length_Winch0] = homed_cable_lengths.lengtha;
        modbus_holding_regs[Current_Length_Winch1] = homed_cable_lengths.lengthb;
        modbus_holding_regs[Current_Length_Winch2] = homed_cable_lengths.lengthc;
        modbus_holding_regs[Current_Length_Winch3] = homed_cable_lengths.lengthd;

        switch(modbus_holding_regs[Winch_ID])
        {
            case 0:
            {
                modbus_holding_regs[Target_Setpoint] = homed_cable_lengths.lengtha;
                break;
            }
            case 1:
            {
                modbus_holding_regs[Target_Setpoint] = homed_cable_lengths.lengthb;
                break;
            }
            case 2:
            {
                modbus_holding_regs[Target_Setpoint] = homed_cable_lengths.lengthc;
                break;
            }
            case 3:
            {
                modbus_holding_regs[Target_Setpoint] = homed_cable_lengths.lengthd;
                break;
            }
        }

        //to ensure no sudden jerk
        //to do: remove jerk from motion profile
        modbus_holding_regs[Current_Encoder_Count] = modbus_holding_regs[Target_Setpoint];
        MotionProfile_reset_position((float) modbus_holding_regs[Target_Setpoint]); //used to remove jerk, not sure if it work yet

        //count = cable_length * pulse_per_revolution * gear_ratio / spool_diameter / PI
        //uint32_t homed_length = (uint32_t)(((float)modbus_holding_regs[Current_Encoder_Count]) * 32.0f * 120.0f / 15.0f / 3.14159265359f);
        uint32_t homed_length = (uint32_t)(((float)modbus_holding_regs[Current_Encoder_Count]) * 81.48733086f);
        homed_length += 0x80000000; //this offset is to allow negative length

        EQEP_setPosition(EQEP1_BASE, homed_length);
    }    
}

void fetch_current_rpm()
{
    //if a full 32-pulse was received (i.e. one full motor revolution has happened)
    if((EQEP_getStatus(EQEP1_BASE) & EQEP_STS_UNIT_POS_EVNT) != 0)
    {
        //
        // No capture overflow, i.e. if 2 consecutive revolutions happened within 10ms
        //
        if((EQEP_getStatus(EQEP1_BASE) & EQEP_STS_CAP_OVRFLW_ERROR) == 0)
        {
            float rpm = (DEVICE_SYSCLK_FREQ / 128.0) / 2.0 / EQEP_getCapturePeriodLatch(EQEP1_BASE) / 4; // 60 seconds / 120 gearbox_ratio = 2
            modbus_holding_regs[Current_RPM] = (int) rpm;
        }


        //
        // Clear unit position event flag and overflow error flag
        //
        EQEP_clearStatus(EQEP1_BASE, (EQEP_STS_UNIT_POS_EVNT |
                                      EQEP_STS_CAP_OVRFLW_ERROR));
    }
    else
    {
        modbus_holding_regs[Current_RPM] = 0;
    }    
}

void check_current_coordinate()
{
    volatile static XYZ_coord_struct actual_point;

    //calculate current point based on cable length
    actual_point = length4_to_XYZ(  (float) modbus_holding_regs[Current_Length_Winch0],
                                    (float) modbus_holding_regs[Current_Length_Winch1],
                                    (float) modbus_holding_regs[Current_Length_Winch2],
                                    (float) modbus_holding_regs[Current_Length_Winch3],
                                    (float) modbus_holding_regs[Field_Length]);

    modbus_holding_regs[Current_X] =  (signed int) actual_point.X;
    modbus_holding_regs[Current_Y] =  (signed int) actual_point.Y;
    modbus_holding_regs[Current_Z] =  (signed int) actual_point.Z;    
}

//used to read all adc on J21 (4 channels) round-robin
void read_all_adc()
{
    //if the conversion was done, fetch all adc results
    if(ADC_getInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1))
    {
        modbus_holding_regs[ADC0] = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER0);
        modbus_holding_regs[ADC1] = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER1);
        modbus_holding_regs[ADC2] = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER2);
        modbus_holding_regs[ADC3] = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER3);
        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);
    }    
}

void manual_control()
{
    static length4_struct target_cable_lengths;
    static XYZ_coord_struct target_point;

    if(modbusRTU_Written && (modbusRTU_written_register_flags[Target_Setpoint]) || modbusRTU_written_register_flags[Target_Setpoint_Offset]) //if length changed
    {
        //clear flags
        modbusRTU_Written = 0;
        modbusRTU_written_register_flags[Target_Setpoint] = 0;
        modbusRTU_written_register_flags[Target_Setpoint_Offset] = 0;

        //update target waypoint
        modbus_holding_regs[Target_Length_Winch0 + modbus_holding_regs[Winch_ID]] = modbus_holding_regs[Target_Setpoint]; 

        target_point = length4_to_XYZ(  (float) modbus_holding_regs[Target_Length_Winch0],
                                        (float) modbus_holding_regs[Target_Length_Winch1],
                                        (float) modbus_holding_regs[Target_Length_Winch2],
                                        (float) modbus_holding_regs[Target_Length_Winch3],
                                        (float) modbus_holding_regs[Field_Length]);

        modbus_holding_regs[Target_X] =  (signed int) target_point.X;
        modbus_holding_regs[Target_Y] =  (signed int) target_point.Y;
        modbus_holding_regs[Target_Z] =  (signed int) target_point.Z;            
    }

    if(modbusRTU_Written && (   modbusRTU_written_register_flags[Target_X] ||
                                modbusRTU_written_register_flags[Target_Y] ||
                                modbusRTU_written_register_flags[Target_Z] )) //if waypoint changed
    {
        //clear flags
        modbusRTU_Written = 0;
        modbusRTU_written_register_flags[Target_X] = 0;
        modbusRTU_written_register_flags[Target_Y] = 0;
        modbusRTU_written_register_flags[Target_Z] = 0;

        //update target length
        target_cable_lengths = XYZ_to_length4(  (float) modbus_holding_regs[Target_X], 
                                                (float) modbus_holding_regs[Target_Y], 
                                                (float) modbus_holding_regs[Target_Z], 
                                                (float) modbus_holding_regs[Field_Length]);

        modbus_holding_regs[Target_Length_Winch0] = target_cable_lengths.lengtha;
        modbus_holding_regs[Target_Length_Winch1] = target_cable_lengths.lengthb;
        modbus_holding_regs[Target_Length_Winch2] = target_cable_lengths.lengthc;
        modbus_holding_regs[Target_Length_Winch3] = target_cable_lengths.lengthd;

        switch(modbus_holding_regs[Winch_ID])
        {
            case 0:
            {
                modbus_holding_regs[Target_Setpoint] = target_cable_lengths.lengtha;
                break;
            }
            case 1:
            {
                modbus_holding_regs[Target_Setpoint] = target_cable_lengths.lengthb;
                break;
            }
            case 2:
            {
                modbus_holding_regs[Target_Setpoint] = target_cable_lengths.lengthc;
                break;
            }
            case 3:
            {
                modbus_holding_regs[Target_Setpoint] = target_cable_lengths.lengthd;
                break;
            }
        }                                            
    }  


    if(modbusRTU_Written && (   modbusRTU_written_register_flags[Target_Length_Winch0] ||
                                modbusRTU_written_register_flags[Target_Length_Winch1] ||
                                modbusRTU_written_register_flags[Target_Length_Winch2] ||
                                modbusRTU_written_register_flags[Target_Length_Winch3] )) //if Target_Length_Winchx changed, transfer it to Target_Setpoint appropriately
    {
        switch(modbus_holding_regs[Winch_ID])
        {
            case 0:
            {
                if(modbusRTU_written_register_flags[Target_Length_Winch0])
                    modbus_holding_regs[Target_Setpoint] = modbus_holding_regs[Target_Length_Winch0];
                break;
            }
            case 1:
            {
                if(modbusRTU_written_register_flags[Target_Length_Winch1])
                    modbus_holding_regs[Target_Setpoint] = modbus_holding_regs[Target_Length_Winch1];
                break;
            }
            case 2:
            {
                if(modbusRTU_written_register_flags[Target_Length_Winch2])
                    modbus_holding_regs[Target_Setpoint] = modbus_holding_regs[Target_Length_Winch2];
                break;
            }
            case 3:
            {
                if(modbusRTU_written_register_flags[Target_Length_Winch3])
                    modbus_holding_regs[Target_Setpoint] = modbus_holding_regs[Target_Length_Winch3];
                break;
            }
        }

        //update target coordinate based on the latest desired lengths
        target_point = length4_to_XYZ(  (float) modbus_holding_regs[Target_Length_Winch0],
                                        (float) modbus_holding_regs[Target_Length_Winch1],
                                        (float) modbus_holding_regs[Target_Length_Winch2],
                                        (float) modbus_holding_regs[Target_Length_Winch3],
                                        (float) modbus_holding_regs[Field_Length]);

        modbus_holding_regs[Target_X] =  (signed int) target_point.X;
        modbus_holding_regs[Target_Y] =  (signed int) target_point.Y;
        modbus_holding_regs[Target_Z] =  (signed int) target_point.Z;     

        //clear flags
        modbusRTU_Written = 0;
        modbusRTU_written_register_flags[Target_Length_Winch0] = 0;
        modbusRTU_written_register_flags[Target_Length_Winch1] = 0;
        modbusRTU_written_register_flags[Target_Length_Winch2] = 0;
        modbusRTU_written_register_flags[Target_Length_Winch3] = 0;        
    }  
}

void auto_mode()
{
    //to do
}

void task_scheduler_handler()
{
    //relative control
    //to do: add simple boundary check to avoid overflow
    modbus_holding_regs[Target_Setpoint] += modbus_holding_regs[Target_Setpoint_Offset];
    modbus_holding_regs[Target_Setpoint_Offset] = 0;

    simple_homing_routine();
    fetch_current_rpm();
    check_current_coordinate();
    read_all_adc();

    if(modbus_holding_regs[Follow_Waypoints] == 0) //if in manual mode, i.e. not using waypoint buffer
    {
        manual_control();
    }    
    /* else // if autonomous mode activated, i.e. using waypoint buffer
    {
        auto_mode();
    } */
}

