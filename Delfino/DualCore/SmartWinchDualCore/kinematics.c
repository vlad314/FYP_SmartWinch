/*
 * kinematics.c
 *
 *  Created on: 14 Feb 2018
 *      Author: [Afdhal Atiff Tan] + [Matthew Danby]
 */


#include "kinematics.h"

int max_val4_loc(float a, float b, float c, float d) {
    //Analyses the four values and returns the location of the Minimum
    //from the four locations (0 through to 3)
    double sel[] = {a, b, c, d};
    int max_val = 0;
    int i;
    for (i=1;i<4;i++) {
        if (sel[i]>sel[max_val])
        max_val = i;

    }
    return max_val;
}

XYZ_coord_struct rotate_about_center(float x, float y, float z, float distance, int rotate) {
    //Sets center of the field to origin instead of motor A
    //Rotate clockwise 90 degrees the number of times specified
    float x_temp = x-(distance/2);
    float y_temp = y-(distance/2);
    XYZ_coord_struct rotated_coord;
    if (rotate==2 || rotate==1) {
        x_temp = x_temp*-1;
    }
    if (rotate==3 || rotate==2) {
        y_temp = y_temp*-1;
    }
    if (rotate==1 || rotate==3) {
        float trans = x_temp;
        x_temp = y_temp;
        y_temp = trans;
    }
    rotated_coord.X = x_temp+(distance/2);
    rotated_coord.Y = y_temp+(distance/2);
    rotated_coord.Z = z;
    return rotated_coord;
}

length4_struct XYZ_to_length4(float X, float Y, float Z, float distance) {
    //Int X,Y and Z are the payload coordinates


    length4_struct lengths;
    lengths.lengtha = sqrt((pow(X,2))+(pow(Y,2))+(pow(Z,2)));
    lengths.lengthb = sqrt((pow(X,2))+(pow((distance-Y),2))+(pow(Z,2)));
    lengths.lengthd = sqrt((pow((distance-X),2))+(pow(Y,2))+(pow(Z,2)));
    lengths.lengthc = sqrt((pow((distance-X),2))+(pow((distance-Y),2))+(pow(Z,2)));
    return lengths;
}

XYZ_coord_struct length4_to_XYZ(float c1, float c2, float c3,float c4,float distance) {
    //a,b and c are the cable lengths respectively
    //Cable d is neglected is this model as assumes no sag at all
    //Distance is the gap between the motors assuming they are...
    //at the same vertical height

    //Rotation of the field is used to simplify maths
    //Field is rotated so that location C becomes the longest cable
    int remove_cable = ((max_val4_loc(c1,c2,c3,c4)+2)%4);
    float array1 [] = {c1,c2,c3,c4};
    float a = array1[(remove_cable)];
    float b = array1[((remove_cable+1)%4)];
    float d = array1[((remove_cable+3))%4];

    //Performs operation
    XYZ_coord_struct coords;
    coords.X = (pow(distance,2)+pow(a,2)-pow(d,2))/(2*distance);
    coords.Y = (pow(distance,2)+pow(a,2)-pow(b,2))/(2*distance);
    coords.Z = sqrt(pow(a,2)-pow(coords.X,2)-pow(coords.Y,2));

    //Rotates field back to original position
    coords = rotate_about_center(coords.X, coords.Y, coords.Z, distance, remove_cable);
    return coords;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


unsigned int total_path_points;
XYZ_coord_struct_int generated_path[1024];

unsigned int max(unsigned int a, unsigned int b, unsigned int c)
{
    if(a>b && a>c)
        return a;
    else if(b>a && b>c)
        return b;
    else
        return c;
}


//taken from http://members.chello.at/easyfilter/bresenham.html
//will return 1 if overflowed
signed long brensenham3d(signed long x0, signed long y0, signed long z0, signed long x1, signed long y1, signed long z1)
{
   signed long dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
   signed long dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
   signed long dz = abs(z1-z0), sz = z0<z1 ? 1 : -1;
   signed long dm = max(dx,dy,dz), i = dm; /* maximum difference */
   x1 = y1 = z1 = dm/2; /* error offset */

   signed long path_pointer = 0, overflowed = 0;

   for(;;) {

      // future: add better point limit check
      if (path_pointer>=1024)
      {
          overflowed = 1;
          break;
      }

      generated_path[path_pointer].X = x0;
      generated_path[path_pointer].Y = y0;
      generated_path[path_pointer].Z = z0;

      path_pointer += 1;

      if (i-- == 0) break;
      x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; }
      y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; }
      z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; }
   }

   total_path_points = path_pointer;
   return overflowed;
}

int32_t length_to_encoder_pulses(int length_in_mm)
{
    //count = cable_length * pulse_per_revolution * gear_ratio / spool_diameter / PI
    //uint32_t count = (uint32_t)(((float)length_in_mm) * 8192.0f * 1.0f / 35.0f / 3.14159265359f);
    return (int32_t)(((float)length_in_mm) * 74.5027025f);
}

int32_t encoder_pulses_to_length(int32_t encoder_pulses)
{
    return (int32_t)(((float) encoder_pulses) / 74.5027025f);
}
