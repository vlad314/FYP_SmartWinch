/*
 * kinematics.c
 *
 *  Created on: 14 Feb 2018
 *      Author: [Afdhal Atiff Tan] + [Matthew Danby] h
 */


#include "kinematics.h"

#define pi 3.14159265358979323846
//w is the weight per unit length of the cable in N/m
//Coordinates of the 3 motors B,C and D. A is assumed as the origin  to begin
//with then the origin is shifted to ensure no negative Coordinates
//Setup assumes flat ground
struct hv_tension_struct {
    float h_ten,v_ten;
};

//struct XYZ_coord_struct {
//    int X,Y,Z;
//    float uplift;
//};

struct input_lengths {
    int ab, cd, ad, ac, bd;
};

//struct length4_struct {
//    int lengtha,lengthb,lengthc,lengthd;
//    int valid_flag;
//};

struct ten4_struct {
    float tena,tenb,tenc,tend;
};

struct matrix3x3 {
    float e11,e12,e13,e21,e22,e23,e31,e32,e33;
};
struct matrix3x1 {
    float e1,e2,e3;
};

struct matrix3x3 matrix_inv_3x3(struct matrix3x3 input) {
    struct matrix3x3 output = input;
    //Calculate determinant
    float det;
    det = input.e11*((input.e22*input.e33)-(input.e23*input.e32));
    det = det-(input.e12*((input.e21*input.e33)-(input.e23*input.e31)));
    det = det+(input.e13*((input.e21*input.e32)-(input.e22*input.e31)));
    det = 1/det;

    //Matrix of minors with transpose included and det multiplication
    output.e11 = det*((input.e22*input.e33)-(input.e23*input.e32));
    output.e21 = det*((input.e21*input.e33)-(input.e23*input.e31));
    output.e31 = det*((input.e21*input.e32)-(input.e22*input.e31));
    output.e12 = det*((input.e12*input.e33)-(input.e13*input.e32));
    output.e22 = det*((input.e11*input.e33)-(input.e13*input.e31));
    output.e32 = det*((input.e11*input.e32)-(input.e12*input.e31));
    output.e13 = det*((input.e12*input.e23)-(input.e13*input.e22));
    output.e23 = det*((input.e11*input.e23)-(input.e13*input.e21));
    output.e33 = det*((input.e11*input.e22)-(input.e12*input.e21));

    //Matrix of cofactors
    output.e12 = output.e12*-1;
    output.e21 = output.e21*-1;
    output.e23 = output.e23*-1;
    output.e32 = output.e32*-1;

    return output;
}

int min_val4_loc(float a, float b, float c, float d) {
    //Analyses the four values and returns the location of the Minimum
    //from the four locations (0 through to 3)
    float sel[] = {a, b, c, d};
    int min_val = 0;
    int i;
    for (i=1;i<4;i++) {
        if (sel[i]<sel[min_val]) 
        min_val = i;
        
    }
    return min_val;
}

struct matrix3x1 matrix_mul_3x3_3x1 (struct matrix3x3 input1, struct matrix3x1 input2) {
    struct matrix3x1 output;
    output.e1 = ((input1.e11*input2.e1)+(input1.e12*input2.e2)+(input1.e13*input2.e3));
    output.e2 = ((input1.e21*input2.e1)+(input1.e22*input2.e2)+(input1.e23*input2.e3));
    output.e3 = ((input1.e31*input2.e1)+(input1.e32*input2.e2)+(input1.e33*input2.e3));
    return output;
}

int max_val4_loc(float a, float b, float c, float d) {
    //Analyses the four values and returns the location of the Minimum
    //from the four locations (0 through to 3)
    float sel[] = {a, b, c, d};
    int max_val = 0;
    int i;
    for (i=1;i<4;i++) {
        if (sel[i]>sel[max_val]) 
        max_val = i;
        
    }
    return max_val;
}

float max_val4(float a, float b, float c, float d) {
    //Analyses the four values and returns the location of the Minimum
    //from the four locations (0 through to 3)
    float sel[] = {a, b, c, d};
    int max_val = 0;
    int i;
    for (i=1;i<4;i++) {
        if (sel[i]>sel[max_val]) 
        max_val = i;
        
    }
    return sel[max_val];
}

float sec(float val) {
  return (1/cos(val));
}

float round1dp(float val) {
    val = val*10.0f;
    val = (val > (floor(val)+0.5f)) ? ceil(val) : floor(val);
    val = val/10.0f;
    return val;
}

float min_max_diff(float g, float h, float i, float j) {
    float min = 1000000;
    float max = 0;
    float arraytest [] = {g,h,i,j};
    int m;
    for (m = 0;m<4;m++) {
        if (min>arraytest[m]) {
            min = arraytest[m];
        }
        if (max<arraytest[m]) {
            max = arraytest[m];
        }
    }
    return (max-min);
}

XYZ_coord_struct length4_to_XYZ(int c1, int c2, int c3,int c4) {
    //a,b and c are the cable lengths respectively
    //Cable d is neglected is this model as assumes no sag at all
    //Distance is the gap between the motors assuming they are...
    //at the same vertical height

    //Rotation of the field is used to simplify maths
    //Field is rotated so that location C becomes the longest cable
    //int remove_cable = ((max_val4_loc(c1,c2,c3,c4)+2)%4);
    //float array1 [] = {c1,c2,c3,c4};
    //float a = array1[(remove_cable)];
    //float b = array1[((remove_cable+1)%4)];
    //float d = array1[((remove_cable+3))%4];
    int a = c1;
    int b = c2;
    int d = c4;

    //Performs operation
    int ab;
    XYZ_coord_struct coords;
    coords.X = (pow((modbus_holding_regs[motdxmm]-modbus_holding_regs[motaxmm]),2)+pow(a,2)-pow(d,2))/(2*(modbus_holding_regs[motdxmm]-modbus_holding_regs[motaxmm]));
    ab = sqrt(pow((modbus_holding_regs[motaymm]-modbus_holding_regs[motbymm]),2)+pow((modbus_holding_regs[motaxmm]-modbus_holding_regs[motbxmm]),2));
    coords.Y = (pow(ab,2)+pow(a,2)-pow(b,2))/(2*ab);
    coords.Z = sqrt(pow(a,2)-pow((coords.X-modbus_holding_regs[motaxmm]),2)-pow((coords.Y-modbus_holding_regs[motaymm]),2));

    //Rotates field back to original position
    //coords = rotate_about_center(coords.X, coords.Y, coords.Z, distance, remove_cable);
    return coords;


}

float ten2hten(float run_l,float h, float ten) {
    float ten_min = 0.1;
    float ten_max = ten;
    float tension_it;
    float mid_it;
    float ten_it;
    int n = 0;
    float ten_dif;
    float ten_dif2;
    float w = ((float) wmm)/1000;
    //Begins iterative solve
    do {
        tension_it = (ten_min+ten_max)/2;
        mid_it = w*run_l/(2*tension_it);
        ten_it = tension_it*sec(atan(sinh(asinh(w*h/(2*tension_it*sinh(mid_it)))-mid_it)));
        
        //Converts to 1 dp
        //ten_it = round1dp(ten_it);
        
        //Checks which limit to keep and which to discard
        if (ten>ten_it) {
            ten_min = tension_it;
        } else {
            ten_max = tension_it;
        }
        n++;
        ten_dif = fabs(ten_it-ten);
        //Continues until desired accuracy reached
    } while(ten_dif>0.1 && n<40);
    //printf("\n%d",n);
    return tension_it;

}

XYZ_coord_struct tenandsag2coord(float tena,float tenb,float tenc,float tend,int slenain,int slenbin,int slencin,int slendin) {
    //Converts the four tensions from the strain gauge and the sagged cable...
    //lengths to the coordinates of the payload
    float X,Y,Z,L1,L2,L3,L4,D1,D2,D3,D4,tenah,tenbh,tench,tendh,va,vb,vc,vd,ka,kb,kc,kd,t1,t2,t3,t4,r1,r2,r3,r4,dif1,dif2,dif3,dif4,maxans,xoff,yoff,tot,tot2,slena,slenb,slenc,slend;
    XYZ_coord_struct output;
    int m,n,maxplace;
    m = 1;
    tot = 100;
    float w = ((float) wmm)/1000;
    //Converts to metres
    slena = ((float) slenain)/1000;
    slenb = ((float) slenbin)/1000;
    slenc = ((float) slencin)/1000;
    slend = ((float) slendin)/1000;
    float motax = ((float) modbus_holding_regs[motaxmm])/1000;
    float motbx = ((float) modbus_holding_regs[motbxmm])/1000;
    float motcx = ((float) modbus_holding_regs[motcxmm])/1000;
    float motdx = ((float) modbus_holding_regs[motdxmm])/1000;
    float motay = ((float) modbus_holding_regs[motaymm])/1000;
    float motby = ((float) modbus_holding_regs[motbymm])/1000;
    float motcy = ((float) modbus_holding_regs[motcymm])/1000;
    float motdy = ((float) modbus_holding_regs[motdymm])/1000;

    //Sets the initial values of x,y and Z
    X = (motax+motbx+motcx+motdx)/4;
    Y = (motay+motby+motcy+motdy)/4;
    Z = 2; //Approximation for now
    //Iterates to find XY values. Compares the values to the sagged length...
    //and keeps iterating until basically match or max number of attempts...
    //reached. Uses taylor series sinh and asinh approximation. XY dominates...
    //terms so approximation for Z used. The closest point to the expression...
    //being correct will be underneath or above the actual payload position...
    //on the z axis. Iterations follow after to calculate the Z coordinate.
    while (m<20 && tot>0.01) {
        m++;
        L1 = sqrt(pow(X-motax,2) + pow(Y,2));
        L2 = sqrt(pow(X-motbx,2) + pow(motby-Y,2));
        L3 = sqrt(pow(motcx-X,2) + pow(motcy-Y,2));
        L4 = sqrt(pow(motdx-X,2) + pow(Y,2));
        D1 = sqrt(pow(X-motax,2) + pow(Y,2)+ pow(Z,2));
        D2 = sqrt(pow(X-motbx,2) + pow(motby-Y,2)+ pow(Z,2));
        D3 = sqrt(pow(motcx-X,2) + pow(motcy-Y,2)+ pow(Z,2));
        D4 = sqrt(pow(motdx-X,2) + pow(Y,2)+ pow(Z,2));
        
        t1 = L1/D1;
        t2 = L2/D2;
        t3 = L3/D3;
        t4 = L4/D4;
        
        tenah = ten2hten(L1,Z,tena);
        tenbh = ten2hten(L2,Z,tenb);
        tench = ten2hten(L3,Z,tenc);
        tendh = ten2hten(L4,Z,tend);

        r1 = w*L1/(2*tenah); //Horizontal tensions approx equal to total
        r2 = w*L2/(2*tenbh);
        r3 = w*L3/(2*tench);
        r4 = w*L4/(2*tendh);
        
        ka = asinh((w*Z)/(2*tenah*sinh(r1)))-r1;
        kb = asinh((w*Z)/(2*tenbh*sinh(r2)))-r2;
        kc = asinh((w*Z)/(2*tench*sinh(r3)))-r3;
        kd = asinh((w*Z)/(2*tendh*sinh(r4)))-r4;
        
        dif1 = (tenah/w)*(sinh(2*r1+ka)-sinh(ka))-slena;
        dif2 = (tenbh/w)*(sinh(2*r2+kb)-sinh(kb))-slenb;
        dif3 = (tench/w)*(sinh(2*r3+kc)-sinh(kc))-slenc;
        dif4 = (tendh/w)*(sinh(2*r4+kd)-sinh(kd))-slend;
        
        float vals[] = {dif1,dif2,dif3,dif4};

        float avers = (dif1,dif2,dif3,dif4)/4;
        maxplace = max_val4_loc(fabs(dif1),fabs(dif2),fabs(dif3),fabs(dif4));
        if (maxplace == 2 || maxplace == 3) {
            xoff = 1;
        } else {
            xoff = -1;
        }
        if (maxplace == 1 || maxplace == 2) {
            yoff = 1;
        } else {
            yoff = -1;
        }
        X = X + (xoff*(vals[(maxplace)]-avers)/3);
        Y = Y + (yoff*(vals[(maxplace)]-avers)/3);
        tot = fabs(dif1)+fabs(dif2)+fabs(dif3)+fabs(dif4);
    }
    
    //XY found, now finds Z
    tot2 = 100;
    n = 1;
    L1 = sqrt(pow(X-motax,2) + pow(Y,2));
    L2 = sqrt(pow(X-motbx,2) + pow(motby-Y,2));
    L3 = sqrt(pow(motcx-X,2) + pow(motcy-Y,2));
    L4 = sqrt(pow(motdx-X,2) + pow(Y,2));
    while (n<20 && tot2>0.05) {
        n++;
        D1 = sqrt(pow(L1,2)+ pow(Z,2));
        D2 = sqrt(pow(L2,2)+ pow(Z,2));
        D3 = sqrt(pow(L3,2)+ pow(Z,2));
        D4 = sqrt(pow(L4,2)+ pow(Z,2));
        
        t1 = L1/D1;
        t2 = L2/D2;
        t3 = L3/D3;
        t4 = L4/D4;
        
        tenah = ten2hten(L1,Z,tena);
        tenbh = ten2hten(L2,Z,tenb);
        tench = ten2hten(L3,Z,tenc);
        tendh = ten2hten(L4,Z,tend);
        
        r1 = w*L1/(2*tenah); //Horizontal tensions approx equal to total
        r2 = w*L2/(2*tenbh);
        r3 = w*L3/(2*tench);
        r4 = w*L4/(2*tendh);
        
        ka = asinh((w*Z)/(2*tenah*sinh(r1)))-r1;
        kb = asinh((w*Z)/(2*tenbh*sinh(r2)))-r2;
        kc = asinh((w*Z)/(2*tench*sinh(r3)))-r3;
        kd = asinh((w*Z)/(2*tendh*sinh(r4)))-r4;
        
        dif1 = (tenah/w)*(sinh(2*r1+ka)-sinh(ka))-slena;
        dif2 = (tenbh/w)*(sinh(2*r2+kb)-sinh(kb))-slenb;
        dif3 = (tench/w)*(sinh(2*r3+kc)-sinh(kc))-slenc;
        dif4 = (tendh/w)*(sinh(2*r4+kd)-sinh(kd))-slend;
        
        tot2 = dif1+dif2+dif3+dif4;
        Z = Z - tot2;
    }
    output.X = (int) (X*1000);
    output.Y = (int) (Y*1000);
    output.Z = (int) (Z*1000);
    //Calculates uplift
    va = tenah*(sinh(2*r1+ka));
    vb = tenbh*(sinh(2*r2+kb));
    vc = tench*(sinh(2*r3+kc));
    vd = tendh*(sinh(2*r4+kd));
    output.uplift = va+vb+vc+vd;
    printf("\nM: ");
    printf("%d",m);
    printf("\nN: ");
    printf("%d",n);
    
    return output;
}

 length4_struct XYZ_to_length4(int X, int Y, int Z) {
    //Int X,Y and Z are the payload coordinates


     length4_struct lengths;
    lengths.lengtha = sqrt((pow(X-modbus_holding_regs[motaxmm],2))+(pow(Y,2))+(pow(Z,2)));
    lengths.lengthb = sqrt((pow(X-modbus_holding_regs[motbxmm],2))+(pow((modbus_holding_regs[motbymm]-Y),2))+(pow(Z,2)));
    lengths.lengthd = sqrt((pow((modbus_holding_regs[motdxmm]-X),2))+(pow(Y,2))+(pow(Z,2)));
    lengths.lengthc = sqrt((pow((modbus_holding_regs[motcxmm]-X),2))+(pow((modbus_holding_regs[motcymm]-Y),2))+(pow(Z,2)));
    lengths.valid_flag = 1;
    return lengths;
}

struct hv_tension_struct angle2tensions(float run_l,float h, float angle) {
    //Initial definitions of the minimum, maximum and current values of tensions
    struct hv_tension_struct ten_ans;
    float ten_min = 0.1;
    float ten_max = 10000;
    float tension_it, mid_it, theta_it, theta_it_d;
    int n = 0;
    float w = ((float) wmm)/1000;
    //Converts angle to 1dp for comparison
    angle = angle*10.0f;
    angle = (angle > (floor(angle)+0.5f)) ? ceil(angle) : floor(angle);
    angle = angle/10.0f;
    
    //Begins iterative solve
    do {
        tension_it = (ten_min+ten_max)/2;
        mid_it = w*run_l/(2*tension_it);
        theta_it = atan(sinh(asinh((w*h)/(2*tension_it*sinh(mid_it)))-mid_it));
        
        //Converts to 1 dp in degrees
        theta_it_d = theta_it*180*10/pi;
        theta_it_d = (theta_it_d > (floor(theta_it_d)+0.5f)) ? ceil(theta_it_d) : floor(theta_it_d);
        theta_it_d = theta_it_d/10.0f;
        
        //Checks which limit to keep and which to discard
        if (angle>theta_it_d) {
            ten_min = tension_it;
        } else {
            ten_max = tension_it;
        }
        n++;
        
        //Continues until desired accuracy reached
    } while(theta_it_d!=angle && n<1000);
    //printf("%f",theta_it);
    ten_ans.h_ten = tension_it;
    //Tension from top
    float thetav_it = atan(sinh(asinh((w*h)/(2*tension_it*sinh(mid_it)))+mid_it));
    ten_ans.v_ten = (tension_it*tan(thetav_it));
    return ten_ans;
}

 length4_struct coord2ten_sag(int xmm, int ymm, int zmm,float comb_uplift) {
    //Takes the slackest cable tension. This is assumed to be the the tension of the cable
    //with the longest chord length and therefore controlled by the motor furthest from the payload
    float x = ((float) xmm)/1000;
    float y = ((float) ymm)/1000;
    float z = ((float) zmm)/1000;
    float w = ((float) wmm)/1000;
    float motax = ((float) modbus_holding_regs[motaxmm])/1000;
    float motbx = ((float) modbus_holding_regs[motbxmm])/1000;
    float motcx = ((float) modbus_holding_regs[motcxmm])/1000;
    float motdx = ((float) modbus_holding_regs[motdxmm])/1000;
    float motay = ((float) modbus_holding_regs[motaymm])/1000;
    float motby = ((float) modbus_holding_regs[motbymm])/1000;
    float motcy = ((float) modbus_holding_regs[motcymm])/1000;
    float motdy = ((float) modbus_holding_regs[motdymm])/1000;

     length4_struct strght_len = XYZ_to_length4(xmm,ymm,zmm);
    float d1 = ((float) strght_len.lengtha)/1000;
    float d2 = ((float) strght_len.lengthb)/1000;
    float d3 = ((float) strght_len.lengthc)/1000;
    float d4 = ((float) strght_len.lengthd)/1000;

    //Finds the longest cable and rotates the field so that cable is now in the location of cable c
    int remove_cable = ((max_val4_loc(d1,d2,d3,d4)+2)%4);
    float array1 [] = {d1,d2,d3,d4};
    float a = array1[(remove_cable)];
    float b = array1[((remove_cable+1)%4)];
    float c = array1[((remove_cable+2)%4)];
    float d = array1[((remove_cable+3))%4];

    //Sets x and Y coordinates for rotated field
    float ax = x-motax;
    float bx = x-motbx;
    float cx = motcx-x;
    float dx = motdx-x;
    float ay = y-motay;
    float by = motby-y;
    float cy = motcy-y;
    float dy = y-motdy;

    float mab = (motby-motay)/(motbx-motax);
    float mbc = (motcy-motby)/(motcx-motbx);
    float mcd = (motcy-motdy)/(motcx-motdx);
    float cab = motay-(mab*motax);
    float cbc = motby-(mbc*motbx);
    float ccd = motcy-(mcd*motcx);


    float lineab = ((y-cab)/mab);
    float linebc = (mbc*x+cbc);
    float linecd = ((y-ccd)/mcd);


    if (((motby-motay)==0)) {
        lineab = modbus_holding_regs[motaxmm];
    }
    if (((motcy-motby)==0)) {
        linebc = motby;
    }
    if (((motcx-motdx)==0)) {
        linecd = motcx;
    }

    if (x<=lineab || y>=linebc || x>=linecd || z<=0) {
        //Invalid result as not in field area
        strght_len.valid_flag = 0;
        return strght_len;
    }


    //Flips the coordinates
    if ((remove_cable==1 || remove_cable==3)) {
    ay = x-motax;
    by = x-motbx;
    cy = motcx-x;
    dy = motdx-x;
    ax = y-motay;
    bx = motby-y;
    cx = motcy-y;
    dx = y-motdy;
    }



    //Coordinates now set so payload in sector A. Although A is now the shortest
    //and C the longest, it checks that B and D coordinates match the lengths
    //as this depends on the position of the payload within the quadrant

        float arrayxswap [] = {ax,bx,cx,dx};
        float arrayyswap [] = {ay,by,cy,dy};
        //Rotates round payload
        ay = arrayyswap[(remove_cable+0)%4];
        by = arrayyswap[(remove_cable+1)%4];
        cy = arrayyswap[(remove_cable+2)%4];
        dy = arrayyswap[(remove_cable+3)%4];
        ax = arrayxswap[(remove_cable+0)%4];
        bx = arrayxswap[(remove_cable+1)%4];
        cx = arrayxswap[(remove_cable+2)%4];
        dx = arrayxswap[(remove_cable+3)%4];




    //Finds and solves matrix equations to find other tensions. This assumes that the sag is negligible in the
    //other cables and the tension in them act along the chord length
    float cxy = sqrt(pow(cx,2)+pow(cy,2));


    //Starts optimisation process
    float min_ang = 0;
    float max_ang = atan(z/cxy)*180/pi;
    float test_ang;
    float Fch,Fcv;
    struct matrix3x3 matA = {(ax/a),(bx/b),(-1*dx/d),(ay/a),(-1*by/b),(dy/d),(z/a),(z/b),(z/d)};
    struct matrix3x3 matAinv = matrix_inv_3x3(matA);
    struct matrix3x1 matB;
    struct matrix3x1 ten_array;
    float ten_out_min[4];
    float ten_out_max[4];
    float ten_out_test[4];
    float ten_out_op[4];
    float min_diff = 0;
    float max_diff = 100000;
    float test_diff = 0;
    float op_diff = 100000;
    float op_ang = 0;
    //Initial min max values
    //Min values
    struct hv_tension_struct tension_c  = angle2tensions(cxy,z, min_ang);
    matB.e1 = (tension_c.h_ten*cx/c);
    matB.e2 = (tension_c.h_ten*cy/c);
    matB.e3 = (comb_uplift-tension_c.v_ten);
    ten_array = matrix_mul_3x3_3x1(matAinv,matB);

    ten_out_min[0] = ten_array.e1;
    ten_out_min[1] = ten_array.e2;
    ten_out_min[2] = sqrt(pow(tension_c.h_ten,2)+pow(tension_c.v_ten,2));
    ten_out_min[3] = ten_array.e3;
    min_diff = min_max_diff(ten_out_min[0],ten_out_min[1],ten_out_min[2],ten_out_min[3]);
    //Max values
    tension_c  = angle2tensions(cxy,z, (max_ang-0.01));
    matB.e1 = (tension_c.h_ten*cx/c);
    matB.e2 = (tension_c.h_ten*cy/c);
    matB.e3 = (comb_uplift-tension_c.v_ten);
    ten_array = matrix_mul_3x3_3x1(matAinv,matB);

    ten_out_max[0] = ten_array.e1;
    ten_out_max[1] = ten_array.e2;
    ten_out_max[2] = sqrt(pow(tension_c.h_ten,2)+pow(tension_c.v_ten,2));
    ten_out_max[3] = ten_array.e3;
    max_diff = min_max_diff(ten_out_max[0],ten_out_max[1],ten_out_max[2],ten_out_max[3]);
    test_ang = min_ang;
    int min_cable;
    do{
        //Number determines steps in analysis
    test_ang=test_ang+(max_ang/50);
    tension_c  = angle2tensions(cxy,z, test_ang);
    matB.e1 = (tension_c.h_ten*cx/c);
    matB.e2 = (tension_c.h_ten*cy/c);
    matB.e3 = (comb_uplift-tension_c.v_ten);
    ten_array = matrix_mul_3x3_3x1(matAinv,matB);

    ten_out_test[0] = ten_array.e1;
    ten_out_test[1] = ten_array.e2;
    ten_out_test[2] = sqrt(pow(tension_c.h_ten,2)+pow(tension_c.v_ten,2));
    ten_out_test[3] = ten_array.e3;

    test_diff = max_val4(ten_out_test[0],ten_out_test[1],ten_out_test[2],ten_out_test[3]);

    min_cable = min_val4_loc(ten_out_test[0],ten_out_test[1],ten_out_test[2],ten_out_test[3]);

    if ((min_cable==2) && (op_diff>test_diff)) {
        op_ang = test_ang;
        op_diff = test_diff;
        ten_out_op[0] = ten_out_test[0];
        ten_out_op[1] = ten_out_test[1];
        ten_out_op[2] = ten_out_test[2];
        ten_out_op[3] = ten_out_test[3];
    //    max_diff = test_diff;
    //} else {
    //    min_ang = test_ang;
    //    min_diff = test_diff;
    }
    //printf("\n%.2f",test_ang);
    //printf(" and %.2f",test_diff);

    //As zero degrees, no vertical force from cable at motor end
    //Force at platform end is equal to cable weight
    //Fch = tension_c.h_ten;

    //float k1 = asinh((w*z)/(2*Fch*sinh((w*cxy)/(2*Fch)))-((w*cxy)/(2*Fch)));
    //float clength_sagged = (Fch/w)*(sinh((w*cxy/Fch)+k1)-sinh(k1));
    //float cweight = clength_sagged*w;

    //As angle is zero degrees at cable motor end
    //Fcv = tension_c.v_ten;


    //Creates matrices to solve as simultaneous equations

    //matB = {(Fch*cx/c),(Fch*cy/c),(comb_uplift-Fcv)};
    //ten_array = matrix_mul_3x3_3x1(matAinv,matB);
    //} while ((max_ang-min_ang)>0.5);
    } while ((min_cable==2));
    printf("\nSlack cable angle with ground: %.2f",op_ang);
    //Optimisation complete so sorts back to original orientation
    //float Fc = sqrt(pow(Fch,2)+pow(Fcv,2));
    //float ten_out[] = {ten_array.e1,ten_array.e2,Fc,ten_array.e3};

    //Finds ascociated Lengths
    float tenah,tenbh,tench,tendh,slena,slenb,slenc,slend,r1,r2,r3,r4,ka,kb,kc,kd;
    tenah = ten2hten(sqrt((ax*ax)+(ay*ay)),z,ten_out_op[0]);
    tenbh = ten2hten(sqrt((bx*bx)+(by*by)),z,ten_out_op[1]);
    tench = ten2hten(sqrt((cx*cx)+(cy*cy)),z,ten_out_op[2]);
    tendh = ten2hten(sqrt((dx*dx)+(dy*dy)),z,ten_out_op[3]);
    
    r1 = w*sqrt((ax*ax)+(ay*ay))/(2*tenah); //Horizontal tensions approx equal to total
    r2 = w*sqrt((bx*bx)+(by*by))/(2*tenbh);
    r3 = w*sqrt((cx*cx)+(cy*cy))/(2*tench);
    r4 = w*sqrt((dx*dx)+(dy*dy))/(2*tendh);
        
    ka = asinh((w*z)/(2*tenah*sinh(r1)))-r1;
    kb = asinh((w*z)/(2*tenbh*sinh(r2)))-r2;
    kc = asinh((w*z)/(2*tench*sinh(r3)))-r3;
    kd = asinh((w*z)/(2*tendh*sinh(r4)))-r4;
        
    slena = (tenah/w)*(sinh(2*r1+ka)-sinh(ka));
    slenb = (tenbh/w)*(sinh(2*r2+kb)-sinh(kb));
    slenc = (tench/w)*(sinh(2*r3+kc)-sinh(kc));
    slend = (tendh/w)*(sinh(2*r4+kd)-sinh(kd));

    float len_out_op[] = {slena,slenb,slenc,slend};
     length4_struct len_final = {(int) (len_out_op[(4-remove_cable)%4]*1000),(int)(len_out_op[(5-remove_cable)%4]*1000),(int)(len_out_op[(6-remove_cable)%4]*1000),(int)(len_out_op[(7-remove_cable)%4]*1000),1};
    struct ten4_struct ten_final = {ten_out_op[(4-remove_cable)%4],ten_out_op[(5-remove_cable)%4],ten_out_op[(6-remove_cable)%4],ten_out_op[(7-remove_cable)%4]};
    //printf("\nTension A: ");
    //printf("%.2f",ten_final.tena);
    //printf("\nTension B: ");
    //printf("%.2f",ten_final.tenb);
    //printf("\nTension C: ");
    //printf("%.2f",ten_final.tenc);
    //printf("\nTension D: ");
    //printf("%.2f",ten_final.tend);
    
    if (slena<=0 || slenb<=0 || slenc<=0 || slend<=0) {
        len_final.valid_flag = 0;
    }
    
    return len_final;
}

void set_motor_coord(int ab, int cd, int ad, int ac, int bd) {
    //Inputs distance between motors and returns the coordiates respective to A
    //Must go negative
    //First assumes motor A at origin and D on x axis
    float motbxt,motbyt,motcxt,motcyt,motdxt, cosdab,coscda;
    motdxt = ad;
    cosdab = ((ad*ad)+(ab*ab)-(bd*bd))/(2*ad*ab);
    motbxt = cosdab*ab;
    motbyt = sqrt((ab*ab)-(motbxt*motbxt));
    
    
    coscda = ((cd*cd)+(ad*ad)-(ac*ac))/(2*cd*ad);
    motcxt = (-coscda*cd);
    motcyt = sqrt((cd*cd)-(motcxt*motcxt));
    motcxt = motcxt + ad;
    
    //Shifts motor coordinates from the origin at motor A to prevent
    //negatives on any of the coordinates
    if (motbxt<0) {
        //Shifts all x coords by B x offset
        modbus_holding_regs[motaxmm] = (int) fabs(motbxt);
        modbus_holding_regs[motbxmm] = 0;
        modbus_holding_regs[motcxmm] = (int) motcxt+fabs(motbxt);
        modbus_holding_regs[motdxmm] = (int) motdxt+fabs(motbxt);
    } else {
        modbus_holding_regs[motaxmm] = 0;
        modbus_holding_regs[motbxmm] = (int) motbxt;
        modbus_holding_regs[motcxmm] = (int) motcxt;
        modbus_holding_regs[motdxmm] = (int) motdxt;
    }
    
    
    modbus_holding_regs[motaymm] = 0;
    modbus_holding_regs[motbymm] = (int) motbyt;
    modbus_holding_regs[motcymm] = (int) motcyt;
    modbus_holding_regs[motdymm] = 0;
}

struct input_lengths mot_coord2sides(int max,int may,int mbx,int mby,int mcx,int mcy,int mdx,int mdy) {
    struct input_lengths kdf;
    kdf.ab = sqrt(pow(max-mbx,2)+pow(may-mby,2));
    kdf.cd = sqrt(pow(mcx-mdx,2)+pow(mcy-mdy,2));
    kdf.ad = sqrt(pow(max-mdx,2)+pow(may-mdy,2));
    kdf.ac = sqrt(pow(max-mcx,2)+pow(may-mcy,2));
    kdf.bd = sqrt(pow(mbx-mdx,2)+pow(mby-mdy,2));
    return kdf;
}
//</new>




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

//this function will update global scaled_speed by using the ratio of cable lengths
//this is so that all winch will finish actuating the tether at around the same time
void update_scaled_velocity(float difference1, float difference2,float difference3,float difference4)
{
    if (dip_switch.BIT4) //this is used to skip scaled velocity
    {
        modbus_holding_regs[scaled_velocity] = modbus_holding_regs[Max_Velocity];
        return;
    }

    float longest_difference = difference1;

    if(longest_difference < difference2)
        longest_difference = difference2;
    if(longest_difference < difference3)
        longest_difference = difference3;
    if(longest_difference < difference4)
        longest_difference = difference4;

    //todo: this section can be simplified using an array
    switch(modbus_holding_regs[Winch_ID])
    {
        case 0:
        {
            modbus_holding_regs[scaled_velocity] = (int)((float)modbus_holding_regs[Max_Velocity]*difference1/longest_difference);
            break;
        }
        case 1:
        {
            modbus_holding_regs[scaled_velocity] = (int)((float)modbus_holding_regs[Max_Velocity]*difference2/longest_difference);
            break;
        }
        case 2:
        {
            modbus_holding_regs[scaled_velocity] = (int)((float)modbus_holding_regs[Max_Velocity]*difference3/longest_difference);
            break;
        }
        case 3:
        {
            modbus_holding_regs[scaled_velocity] = (int)((float)modbus_holding_regs[Max_Velocity]*difference4/longest_difference);
            break;
        }
    }     
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

float pulse_length_scaler()
{
    return  ((float)modbus_holding_regs[Encoder_Pulse]) /
            ((float)modbus_holding_regs[Encoder_Radius]*2.0f*3.14159265359f/1000.0f);
}

int32_t length_to_encoder_pulses(int length_in_mm)
{
    //count = cable_length * pulse_per_revolution * gear_ratio / spool_diameter / PI
    //uint32_t count = (uint32_t)(((float)length_in_mm) * 8192.0f * 1.0f / 35.0f / 3.14159265359f);
    return (int32_t) (((float)length_in_mm) * pulse_length_scaler()); // was 74.5027025, 81.48733086f
}

int32_t encoder_pulses_to_length(int32_t encoder_pulses)
{
    return (int32_t)(((float) encoder_pulses) / pulse_length_scaler()); //(8192.0f / ((float)modbus_holding_regs[Encoder_Radius] * 2.0f) / 3.14159265359f));
}

//this function is used for fetching waypoints from modbus buffer
//axis X,Y,Z is mapped to 0,1,2
uint32_t waypoints(int index, int axis)
{
    return (uint32_t) modbus_holding_regs[X1 + (index*3) + axis];
}
