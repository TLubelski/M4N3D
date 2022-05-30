#include "kinematics.h"


double deg2rad(double deg) { return (deg/180.0f) * M_PI; }

double rad2deg(double rad) { return rad * (180.0f / M_PI); }

uint16_t rad2srv(double rad) { return (rad/M_PI)*512 + 512; }

uint16_t deg2srv(double deg){ return (deg/180.0f)*512 + 512; }

double srv2rad(uint16_t srv){ return (((double)srv-512.0f)/512.0f)*M_PI; }

double srv2deg(uint16_t srv){ return (((double)srv-512.0f)/512.0f)*180.0f; }

bool KS_calc_IK(double x, double y, double z)
{
    double q1, q2, q3;
    double r1, r2, r3, phi1, phi2;

    double l1 = RobotParams.l1;     // base to q2
    double l2 = RobotParams.l2;     // q2 to q3
    double l3 = RobotParams.l3;    	// q3 to efector
    double l4 = RobotParams.l4;     // right shift
    double l5 = RobotParams.l5;     // efector height

    q1 = 2 * atan( (x - sqrt( x*x + y*y - l4*l4 )) / ( l4-y ) );
    r1 = sqrt( x*x + pow( y+l4/cos(q1), 2) ) - l4*tan(q1);
    r2 = z - l1 + l5;
    r3 = sqrt( r1*r1 + r2*r2 );
    phi1 = atan( r2 / r1 );
    phi2 = M_PI/2 - phi1;
    q2 = acos( ( l3*l3 - l2*l2 - r3*r3 ) / (-2*l2*r3) ) - phi2;
    q3 = acos( ( r3*r3 - l2*l2 - l3*l3 ) / (-2*l2*l3) ) - M_PI/2;

    //check for NaN
    if(q1 != q1 || q2 != q2 || q3 != q3)
        return false;

    RobotParams.q1 = RobotParams.q1_off + q1;
    RobotParams.q2 = RobotParams.q2_off + q2;
    RobotParams.q3 = RobotParams.q3_off + q3;

    RobotParams.x = x;
    RobotParams.y = y;
    RobotParams.z = z;

    return true;
}

void KS_calc_FK()
{
    double l1 = RobotParams.l1;     // base to q2
    double l2 = RobotParams.l2;     // q2 to q3
    double l3 = RobotParams.l3;    	// q3 to efector
    double l4 = RobotParams.l4;     // right shift
    double l5 = RobotParams.l5;     // efector height

    double q1 = RobotParams.aq1 - RobotParams.q1_off;
    double q2 = RobotParams.aq2 - RobotParams.q2_off;
    double q3 = RobotParams.aq3 - RobotParams.q3_off;

    RobotParams.ax = -l2*sin(q2)*cos(q1) + l3*cos(q1)*cos(q2 + q3) + l4*sin(q1);
    RobotParams.ay = -l2*sin(q1)*sin(q2) + l3*sin(q1)*cos(q2 + q3) - l4*cos(q1);
    RobotParams.az = l1 + l2*cos(q2) + l3*sin(q2 + q3) - l5;
}






