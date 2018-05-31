#include <stdio.h>
#include <math.h>
#include "intermediate_waypoints.h"


minimum_int intermediate_waypoint(  int start_x, int start_y, int start_z, int finish_x, int finish_y, int finish_z, int winch_id, int motaxmm, int motaymm, int motbxmm, int motbymm, int motcxmm, int motcymm, int motdxmm, int motdymm)
{
	


float startx = (float) start_x;
float starty = (float) start_y;
float startz = (float) start_z;
float finishx = (float) finish_x;
float finishy = (float) finish_y;
float finishz = (float) finish_z;




  //float limit = (float)fieldlength - ( (float)fieldlength*sqrt(2) / ( (float)numberOfSegments+1));

  // if (startx > fieldlength )
  //   startx = fieldlength;
  // if (starty > fieldlength )
  //   starty = fieldlength;
  // if (finishx > fieldlength )
  //   finishx = fieldlength;
  // if (finishy > fieldlength )
  //   finishy = fieldlength;

  //   if (startx < 0 )
  //   startx = 0;
  // if (starty < 0 )
  //   starty = 0;
  // if (finishx < 0 )
  //   finishx = 0;
  // if (finishy < 0 )
  //   finishy = 0;

  if (winch_id < 0)
    winch_id = 0;
  if (winch_id > 3)
    winch_id = 3;


  // float dsw1, dsw2, dsw3, dsw0;
  // float dfw1, dfw2, dfw3, dfw0;
  float dsw;
  float dfw;
  float dsf;
  float semip0, area, height, x, y, dsf_2d, m, a, b, c, delta, xd1, xd2, xd, mz, yd, zd, d;


  //  dsw0 = sqrt(startx*startx + starty*starty + startz*startz);
  //     dfw0 = sqrt(finishx*finishx + finishy*finishy + finishz*finishz);



  switch (winch_id) {
    case 0 : {
      dsw = sqrt((startx+motaxmm)*(startx+motaxmm) + starty*starty + startz*startz);
      dfw = sqrt((finishx+motaxmm)*(finishx+motaxmm) + finishy*finishy + finishz*finishz);
     // printf("0dsw0 = %.2f, dfw0 = %.2f\n", dsw, dfw);
      break;
    }
    case 1 : {
      dsw = sqrt((startx+motbxmm)*(startx+motbxmm) + (motbymm - starty)*(motbymm - starty) + startz*startz);
      dfw = sqrt((finishx+motbxmm)*(finishx+motbxmm) + (motbymm - finishy)*(motbymm - finishy) + finishz*finishz);
     // printf("1dsw0 = %.2f, dfw0 = %.2f\n", dsw, dfw);
      break;
    }
    case 2 : {
      dsw = sqrt((motcxmm - startx)*(motcxmm - startx) + (motcymm - starty)*(motcymm - starty) + startz*startz);
      dfw = sqrt((motcxmm - finishx)*(motcxmm - finishx) + (motcymm - finishy)*(motcymm - finishy) + finishz*finishz);
      //printf("2dsw0 = %.2f, dfw0 = %.2f\n", dsw, dfw);
      break;
    }
    case 3 : {
      dsw = sqrt((motdxmm - startx)*(motdxmm - startx) + starty*starty + startz*startz);
      dfw = sqrt((motdxmm - finishx)*(motdxmm - finishx) + finishy*finishy + finishz*finishz);
      //printf("3dsw0 = %.2f, dfw0 = %.2f\n", dsw, dfw);
      break;
    }
  }
      // printf("dsw0 = %.2f, dfw0 = %.2f\n", dsw, dfw);
  dsf = sqrt((finishx - startx)*(finishx - startx) + (finishy - starty)*(finishy - starty) + (finishz - startz)*(finishz - startz));
  //printf("dsf= %.2f\n", dsf);


  semip0 = (dsw + dfw + dsf)/2;
  // printf("semip0 = %.2f\n", semip0);

  area = sqrt(semip0*(semip0-dsf)*(semip0-dsw)*(semip0-dfw));

  //printf("area = %.2f\n", area);

  height = 2* (area/dsf);
  //printf("height = %.2f\n", height);

  x = sqrt(dfw*dfw - height*height);
  y = sqrt(dsw*dsw - height*height);
  //printf("x = %.2f\n", x);
 // printf("y = %.2f\n", y);


  dsf_2d = sqrt((finishx - startx)*(finishx - startx) + (finishy - starty)*(finishy - starty));
  //printf("dsf_2d = %.2f\n", dsf_2d );

  d = dsf_2d - ((x * dsf_2d)/dsf);
  //printf("d = %.2f\n\n", d );

  // if (d < 0)


  
  // printf("finishy = %d\n", finishy );
  if (finishx == startx)
    finishx *= 1.01;

  // printf("finishx = %d\n", finishx );
  float fyx = (float)finishy-(float)starty;
    // printf("finishy = %.2f\n", fyx );
  float syx = ((float)finishx-(float)startx);
  m = fyx/(syx);

  // printf("m = %.2f\n", m );


  xd = ((1-d/dsf_2d))*startx + ((d/dsf_2d)*finishx) + motaxmm;
  // printf("xd = %.2f\n", xd );
  yd = m*xd - (-finishy + m*finishx);	

  mz = finishz - startz;

  zd = (mz/(float)(finishx-startx))*(xd - (float)startx) + (float)startz;	
// printf("\n startx = %.2f, finishx = %.2f, zd = %.2f\n", startx, finishx, zd);
  if (area == 0){
    if (startx <= finishx){
        if (winch_id == 0 || winch_id == 1){
          //  printf("\n[[1]]\n");
          xd = startx;
          // printf("\n [[]]startx = %.2f, finishx = %.2f, zd = %.2f\n", xd, yd, zd);

          yd = starty;
          zd = startz;
        }
        else if (winch_id == 2 || winch_id == 3){
        // printf("[[2]]");
          xd = finishx;
          yd = finishy;
          zd = finishz;
        }
    }
    else if (startx > finishx){
        if (winch_id == 0 || winch_id == 1){
          // printf("[[3]]");
          xd = finishx;
          yd = finishy;
          zd = finishz;
          
        }
        else if (winch_id == 2 || winch_id == 3){
          // printf("[[4]]");
          xd = startx;
          yd = starty;
          zd = startz;
        }
    }
  }
  else {
    if (x > dsf_2d || y > dsf_2d){
      // printf("\n--2--\n");
      if (x > y){
        xd = startx;
        yd = starty;
        zd = startz;
      }
      else if (x < y){
          xd = finishx;
          yd = finishy;
          zd = finishz;
      }
    }
    // else if (y > dsf_2d){
    //   // printf("\n--3--\n");
    //   if (x > y){
    //     xd = startx;
    //     yd = starty;
    //     zd = startz;
    //   }
    //   else if (y > x){
    //       xd = finishx;
    //       yd = finishy;
    //       zd = finishz;
    //   }
    // }
  }
// printf("\n [[-]]startx = %.2f, finishx = %.2f, zd = %.2f\n", xd, yd, zd);
  if (dsf_2d == 0){
    if (startz > finishz)
      zd = finishz;
    else
      zd = startz;
  }

  minimum_int out;
  // printf("\n1) xd = %.2f, yd = %.2f, zd = %.2f \n",  xd,  yd,  zd);
  out.min_x = (int) xd;
  // printf("\n xd = %.2f, yd = %.2f, zd = %.2f\n", startx, yd, zd);
  // printf("\n xd = %d, yd = %d, zd = %d \n",  out.min_x,  out.min_y,  out.min_z);
  out.min_y = (int) yd;
  out.min_z = (int) zd;

  //   printf("\n xd = %d, yd = %d, zd = %d \n",  out.min_x,  out.min_y,  out.min_z);
  // printf("\n xd = %.2f, yd = %.2f, zd = %.2f\n\n", xd, yd, zd);

  return out;

}
