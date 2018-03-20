//temporary pid
/*
volatile float setpoint = 7680.0;
volatile float kp=0.0,ki=0.0,kd=700;
volatile float error=0.0, input_previous=0.0, error_integrated=0.0, input_differentiated=0.0;
volatile float out_min = -8000000.0, out_max = 8000000.0;
volatile float input=0.0, output=0.0;*/

/*
    input = (float) EQEP_getPositionLatch(EQEP1_BASE);

    //<Proportional>
    error = setpoint - input;
    output = kp*error;
    //</Proportional>

    //<Integration>
    error_integrated += error;

    //preventing integrator windup
    error_integrated = error_integrated > out_max ? out_max : error_integrated;
    error_integrated = error_integrated < out_min ? out_min : error_integrated;

    //reseting integrator
    if(ki == 0.0)
        error_integrated = 0.0;

    output += ki/1000.0*error_integrated; //added divide by 1000 to allow for fractional math
    //</Integration>

    //<Differentiation> (�Derivative on Measurement�)
    input_differentiated = input - input_previous;
    input_previous = input;

    output -= kd * input_differentiated;
    //</Differentiation>

    //output clamp
    output = output > out_max ? out_max : output;
    output = output < out_min ? out_min : output;

    bidirectional_motor((signed long) output);
*/






volatile static length4_struct cable_lengths;




/*     //auto mode means using kinematic maths
    if(modbus_holding_regs[Kinematic_mode]!=0)
    {
        cable_lengths = XYZ_to_length4((float) modbus_holding_regs[Target_X], (float) modbus_holding_regs[Target_Y], (float) modbus_holding_regs[Target_Z], (float) modbus_holding_regs[Field_Length]);

        switch(modbus_holding_regs[Winch_ID])
        {
            case 0:
            {
                modbus_holding_regs[Target_Setpoint] = cable_lengths.lengtha;
                break;
            }
            case 1:
            {
                modbus_holding_regs[Target_Setpoint] = cable_lengths.lengthb;
                break;
            }
            case 2:
            {
                modbus_holding_regs[Target_Setpoint] = cable_lengths.lengthc;
                break;
            }
            case 3:
            {
                modbus_holding_regs[Target_Setpoint] = cable_lengths.lengthd;
                break;
            }
        }
    } */