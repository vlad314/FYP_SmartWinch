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
typedef struct {
    float X,Y,Z;
} XYZ_coord_struct;

typedef struct {
    float lengtha,lengthb,lengthc,lengthd;
} length4_struct;

length4_struct XYZ_to_length4(float X, float Y, float Z, float distance);
XYZ_coord_struct length4_to_XYZ(float a, float b, float c, float distance);
//</Matt Danby>



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Afdhal Atiff Tan>
typedef struct {
    unsigned int X,Y,Z;
} XYZ_coord_struct_int;

extern XYZ_coord_struct_int generated_path[1024]; // maximum distance between points is 1.024 meters
extern unsigned int total_path_points;

signed long brensenham3d(signed long x0, signed long y0, signed long z0, signed long x1, signed long y1, signed long z1);
//</Afdhal Atiff Tan>


#endif /* KINEMATICS_H_ */
