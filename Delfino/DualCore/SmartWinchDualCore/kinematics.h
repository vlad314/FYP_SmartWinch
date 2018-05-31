/*
 * kinematics.h
 *
 *  Created on: 14 Feb 2018
 *      Author: AfdhalAtiffTan
 */

#ifndef KINEMATICS_H_
#define KINEMATICS_H_

#include "includes.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Matt Danby>
//typedef struct {
//    float X,Y,Z,uplift;
//} XYZ_coord_struct;

typedef struct  {
    int X,Y,Z;
    float uplift;
} XYZ_coord_struct;

typedef struct  {
    int lengtha,lengthb,lengthc,lengthd;
    int valid_flag;
} length4_struct;

//typedef struct {
//    float lengtha,lengthb,lengthc,lengthd;
//} length4_struct;

//length4_struct XYZ_to_length4(float X, float Y, float Z);
//XYZ_coord_struct length4_to_XYZ(float c1, float c2, float c3,float c4,float distance);

 XYZ_coord_struct length4_to_XYZ(int c1, int c2, int c3,int c4);
XYZ_coord_struct tenandsag2coord(float tena,float tenb,float tenc,float tend,int slenain,int slenbin,int slencin,int slendin);
length4_struct XYZ_to_length4(int X, int Y, int Z);
void set_motor_coord(int ab, int cd, int ad, int ac, int bd);
length4_struct coord2ten_sag(int xmm, int ymm, int zmm,float comb_uplift);


//XYZ_coord_struct tenandsag2coord(float tena,float tenb,float tenc,float tend,float slena,float slenb,float slenc,float slend,float distance);
//length4_struct coord2ten_sag(float x, float y, float z,float distance,float comb_uplift);

//</Matt Danby>



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Afdhal Atiff Tan>
typedef struct {
    unsigned int X,Y,Z;
} XYZ_coord_struct_int;

extern XYZ_coord_struct_int generated_path[1024]; // maximum distance between points is 1.024 meters
extern unsigned int total_path_points;

signed long brensenham3d(signed long x0, signed long y0, signed long z0, signed long x1, signed long y1, signed long z1);

void update_scaled_velocity(float length1, float length2,float length3,float length4);
int32_t length_to_encoder_pulses(int length_in_mm);
int32_t encoder_pulses_to_length(int32_t encoder_pulses);
uint32_t waypoints(int index, int axis);
//</Afdhal Atiff Tan>


#endif /* KINEMATICS_H_ */
