/*
 * kinematics.c
 *
 *  Created on: 14 Feb 2018
 *      Author: [Afdhal Atiff Tan] + [Matthew Danby]
 */


#include "kinematics.h"

length4_struct XYZ_to_length4(float X, float Y, float Z, float distance) {
    //Int X,Y and Z are the payload coordinates

    length4_struct lengths;

    lengths.lengtha = sqrt((pow(X,2))+(pow(Y,2))+(pow(Z,2)));
    lengths.lengthb = sqrt((pow((distance-X),2))+(pow(Y,2))+(pow(Z,2)));
    lengths.lengthc = sqrt((pow(X,2))+(pow((distance-Y),2))+(pow(Z,2)));
    lengths.lengthd = sqrt((pow((distance-X),2))+(pow((distance-Y),2))+(pow(Z,2)));

    return lengths;
}

XYZ_coord_struct length4_to_XYZ(float a, float b, float c, float distance) {
    //a,b and c are the cable lengths respectively
    //Cable d is neglected is this model as assumes no sag at all
    //Distance is the gap between the motors assuming they are...
    //at the same vertical height
    XYZ_coord_struct coords;

    coords.X = (pow(distance,2)+pow(a,2)-pow(b,2))/(2*distance);
    coords.Y = (pow(distance,2)+pow(b,2)-pow(c,2))/(2*distance);
    coords.Z = sqrt(pow(a,2)-pow(coords.X,2)-pow(coords.Y,2));

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
