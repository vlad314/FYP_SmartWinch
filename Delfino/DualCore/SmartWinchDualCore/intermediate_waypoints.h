//Author: Vlad Savu
//This function calculates the coordinate at which the length of the tether is minimum for a specific 
//winch, over a straight line followed by the payload, starting from point Start(start_x,start_y,start_z) and finishing at Finish(finish_x,finish_y,finish_z)
//inputs: startx = x coordinate of the start point
//		  finishx = x coordinate of the finish point
//		  winchid
//        fieldlength
//output: data structure with the 3 coordinates x,y,z of the point where the tether length is minimum for the specified winch

#ifndef INTERMa_H1_
#define INTERMa_H1_

#include <stdio.h>
#include <math.h>
#include "intermediate_wpts_noLoop.h"
#include "includes.h"

minimum_int intermediate_waypoint(  int start_x, int start_y, int start_z, int finish_x,
                                int finish_y, int finish_z, int winch_id, int motaxmm, int motaymm, int motbxmm, int motbymm, int motcxmm, int motcymm, int motdxmm, int motdymm);
	

#endif /* INTERMa_H1_ */
