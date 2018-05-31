/*
 * autonomous_mode.c
 *
 *  Created on: 16 May 2018
 *      Author: AfdhalAtiffTan
 */

#include "autonomous_mode.h"

//this function will only update the target setpoint in the hreg
void waypoint_follower()
{
    static length4_struct target_cable_lengths, current_cable_lengths;
    static int previous_mode = 0;
    int dist_wpt_w1, dist_wpt_w2, dist_wpt_w3, dist_wpt_w4;
    int dist [4];
    minimum_int pts[4];
    int swap, min, i, flag, current_x, current_y, current_z, j;
    minimum_int wpt_w1, wpt_w2, wpt_w3, wpt_w4;
    
    if (modbus_holding_regs[Current_Waypoints_Pointer] < modbus_holding_regs[Number_of_Waypoints])
    {
        //calculate the coordinates of the next waypoint
        modbus_holding_regs[Target_X] = waypoints(modbus_holding_regs[Current_Waypoints_Pointer], 0);
        modbus_holding_regs[Target_Y] = waypoints(modbus_holding_regs[Current_Waypoints_Pointer], 1);
        modbus_holding_regs[Target_Z] = waypoints(modbus_holding_regs[Current_Waypoints_Pointer], 2);

        //record the current distances from the winches to the payload
        current_cable_lengths = XYZ_to_length4(  (float) modbus_holding_regs[Current_Waypoints_Pointer ],
                                                (float) modbus_holding_regs[Current_Waypoints_Pointer + 1],
                                                (float) modbus_holding_regs[Current_Waypoints_Pointer + 2],
                                                (float) modbus_holding_regs[Field_Length]); //what if the field is not square?

        current_x = modbus_holding_regs[Current_Waypoints_Pointer];
        current_y = modbus_holding_regs[Current_Waypoints_Pointer + 1];
        current_z = modbus_holding_regs[Current_Waypoints_Pointer + 2];

        //calculate the coordinates of the minimum tether length for winch 1
        wpt_w1 = intermediate_waypoint(modbus_holding_regs[Current_Waypoints_Pointer],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 1],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 2],
                                       modbus_holding_regs[Target_X],
                                       modbus_holding_regs[Target_Y],
                                       modbus_holding_regs[Target_Z],
                                       0,
                                       modbus_holding_regs[motaxmm],
                                       modbus_holding_regs[motaymm],
                                       modbus_holding_regs[motbxmm],
                                       modbus_holding_regs[motbymm],
                                       modbus_holding_regs[motcxmm],
                                       modbus_holding_regs[motcymm],
                                       modbus_holding_regs[motdxmm],
                                       modbus_holding_regs[motdymm]
                                       );
        //calculate the coordinates of the minimum tether length for winch 2
        wpt_w2 = intermediate_waypoint(modbus_holding_regs[Current_Waypoints_Pointer],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 1],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 2],
                                       modbus_holding_regs[Target_X],
                                       modbus_holding_regs[Target_Y],
                                       modbus_holding_regs[Target_Z],
                                       1,
                                       modbus_holding_regs[motaxmm],
                                       modbus_holding_regs[motaymm],
                                       modbus_holding_regs[motbxmm],
                                       modbus_holding_regs[motbymm],
                                       modbus_holding_regs[motcxmm],
                                       modbus_holding_regs[motcymm],
                                       modbus_holding_regs[motdxmm],
                                       modbus_holding_regs[motdymm]
                                       );

        //calculate the coordinates of the minimum tether length for winch 3
        wpt_w3 = intermediate_waypoint(modbus_holding_regs[Current_Waypoints_Pointer],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 1],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 2],
                                       modbus_holding_regs[Target_X],
                                       modbus_holding_regs[Target_Y],
                                       modbus_holding_regs[Target_Z],
                                       2,
                                       modbus_holding_regs[motaxmm],
                                       modbus_holding_regs[motaymm],
                                       modbus_holding_regs[motbxmm],
                                       modbus_holding_regs[motbymm],
                                       modbus_holding_regs[motcxmm],
                                       modbus_holding_regs[motcymm],
                                       modbus_holding_regs[motdxmm],
                                       modbus_holding_regs[motdymm]
                                       );

        //calculate the coordinates of the minimum tether length for winch 4
        wpt_w4 = intermediate_waypoint(modbus_holding_regs[Current_Waypoints_Pointer],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 1],
                                       modbus_holding_regs[Current_Waypoints_Pointer + 2],
                                       modbus_holding_regs[Target_X],
                                       modbus_holding_regs[Target_Y],
                                       modbus_holding_regs[Target_Z],
                                       3,
                                       modbus_holding_regs[motaxmm],
                                       modbus_holding_regs[motaymm],
                                       modbus_holding_regs[motbxmm],
                                       modbus_holding_regs[motbymm],
                                       modbus_holding_regs[motcxmm],
                                       modbus_holding_regs[motcymm],
                                       modbus_holding_regs[motdxmm],
                                       modbus_holding_regs[motdymm]
                                       );



        //calculate distances between each point of minimum tether length and the start coordinate
        dist_wpt_w1 = (int) sqrt((wpt_w1.min_x - current_x)*(wpt_w1.min_x - current_x) + (wpt_w1.min_y - current_y)*(wpt_w1.min_y - current_y) + (wpt_w1.min_z - current_z)*(wpt_w1.min_z - current_z));
        dist_wpt_w2 = (int) sqrt((wpt_w1.min_x - current_x)*(wpt_w2.min_x - current_x) + (wpt_w2.min_y - current_y)*(wpt_w2.min_y - current_y) + (wpt_w2.min_z - current_z)*(wpt_w2.min_z - current_z));
        dist_wpt_w3 = (int) sqrt((wpt_w1.min_x - current_x)*(wpt_w3.min_x - current_x) + (wpt_w3.min_y - current_y)*(wpt_w3.min_y - current_y) + (wpt_w3.min_z - current_z)*(wpt_w3.min_z - current_z));
        dist_wpt_w4 = (int) sqrt((wpt_w1.min_x - current_x)*(wpt_w4.min_x - current_x) + (wpt_w4.min_y - current_y)*(wpt_w4.min_y - current_y) + (wpt_w4.min_z - current_z)*(wpt_w4.min_z - current_z));


        //sort the distances in ascending order
        dist[0] = dist_wpt_w1;
        dist[1] = dist_wpt_w2;
        dist[2] = dist_wpt_w3;
        dist[3] = dist_wpt_w4;
        while (min > 0){
            for (i = 1; i <= min; i++){
                if (dist[i-1] > dist[i]){
                    swap = dist[i-1];
                    dist[i-1] = dist[i];
                    dist[i] = swap;
                }
            }
            min -= 1;
        }
        for (i = 0; i <= 3; i++){
            if (dist[0] == dist_wpt_w1)
                pts[0] = wpt_w1;
            else if (dist[1] == dist_wpt_w2)
                pts[1] = wpt_w2;
            else if (dist[0] == dist_wpt_w3)
                pts[2] = wpt_w3;
            else if (dist[0] == dist_wpt_w4)
                pts[3] = wpt_w4;
        }

        //run through the intemrediate waypoints
        for ( j = 0; j <= 4; j++){
            if (j != 4)
                if (j >= 1 && dist[j] == dist[j-1])
                    continue;
                else if (j == 4){
                    //update target length
                    target_cable_lengths = XYZ_to_length4(  (float) modbus_holding_regs[Target_X],
                                                            (float) modbus_holding_regs[Target_Y],
                                                            (float) modbus_holding_regs[Target_Z],
                                                            (float) modbus_holding_regs[Field_Length]);

                    modbus_holding_regs[Target_Length_Winch0] = target_cable_lengths.lengtha;
                    modbus_holding_regs[Target_Length_Winch1] = target_cable_lengths.lengthb;
                    modbus_holding_regs[Target_Length_Winch2] = target_cable_lengths.lengthc;
                    modbus_holding_regs[Target_Length_Winch3] = target_cable_lengths.lengthd;

                    update_scaled_velocity( target_cable_lengths.lengtha - current_cable_lengths.lengtha,
                                        target_cable_lengths.lengthb - current_cable_lengths.lengthb,
                                        target_cable_lengths.lengthc - current_cable_lengths.lengthc,
                                        target_cable_lengths.lengthd - current_cable_lengths.lengthd);

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

                    if(modbus_holding_regs[tether_reached_target])
                    {
                        static uint32_t last_timestamp = 0;

                        if(modbus_holding_regs[Follow_Waypoints] != previous_mode) //if mode was changed
                            last_timestamp = systick();
                        previous_mode = modbus_holding_regs[Follow_Waypoints];

                        if (systick() - last_timestamp > (5000*(uint32_t)modbus_holding_regs[Dwell_Time]))
                        {
                            modbus_holding_regs[Current_Waypoints_Pointer]+=1;
                            last_timestamp = systick();
                        }
                    }
                }
                else {
                    //calculate the target cable lengths from the coordinates of each intermediate waypoint
                    target_cable_lengths = XYZ_to_length4(  (float) pts[j].min_x,
                                                            (float) pts[j].min_y,
                                                            (float) pts[j].min_z,
                                                            (float) modbus_holding_regs[Field_Length]);

                    //update the target lengths
                    modbus_holding_regs[Target_Length_Winch0] = target_cable_lengths.lengtha;
                    modbus_holding_regs[Target_Length_Winch1] = target_cable_lengths.lengthb;
                    modbus_holding_regs[Target_Length_Winch2] = target_cable_lengths.lengthc;
                    modbus_holding_regs[Target_Length_Winch3] = target_cable_lengths.lengthd;

                    //scale velocities
                    update_scaled_velocity( target_cable_lengths.lengtha - current_cable_lengths.lengtha,
                                        target_cable_lengths.lengthb - current_cable_lengths.lengthb,
                                        target_cable_lengths.lengthc - current_cable_lengths.lengthc,
                                        target_cable_lengths.lengthd - current_cable_lengths.lengthd);

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

                    if(modbus_holding_regs[tether_reached_target])
                    {
                        static uint32_t last_timestamp = 0;

                        if(modbus_holding_regs[Follow_Waypoints] != previous_mode) //if mode was changed
                            last_timestamp = systick();
                        previous_mode = modbus_holding_regs[Follow_Waypoints];

                        if (systick() - last_timestamp > (5000*(uint32_t)modbus_holding_regs[Dwell_Time]))
                        {
                            modbus_holding_regs[Current_Waypoints_Pointer]+=1;
                            last_timestamp = systick();
                        }
                    }
                }
            }

        }
    else
    {
        modbus_holding_regs[Follow_Waypoints] = 0;
        modbus_holding_regs[Current_Waypoints_Pointer] = 0;
        previous_mode = 0;
    }
}
