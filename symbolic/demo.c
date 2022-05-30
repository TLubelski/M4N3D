#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef M_PI
#define M_PI   3.14159265358979323846264338327950288f
#endif

#define L1 44.5
#define L2 83.2
#define L3 136.3
#define L4 31.75
#define L5 37.6
#define Q1_OFF 0
#define Q2_OFF 16
#define Q3_OFF -5


double deg2rad(double deg) { return (deg/180.0f) * M_PI; }

double rad2deg(double rad) { return rad * (180.0f / M_PI); }

uint16_t rad2srv(double rad) { return (rad/M_PI)*512 + 512; }

uint16_t deg2srv(double deg){ return (deg/180.0f)*512 + 512; }


typedef struct{
    double l1, l2, l3, l4, l5;
    double q1_off, q2_off, q3_off;
    double q1, q2, q3;
    double x, y, z;
    double ax, ay, az;
} Kinematics;


void Kinematics_Init(Kinematics* ks, double l1, double l2, double l3, double l4, double l5, double q1_off, double q2_off, double q3_off )
{
    ks->l1 = l1;     // base to q2
    ks->l2 = l2;     // q2 to q3 
    ks->l3 = l3;    // q3 to efector
    ks->l4 = l4;     // right shift
    ks->l5 = l5;     // efector height

    ks->q1_off = q1_off;
    ks->q2_off = q2_off;
    ks->q3_off = q3_off;

    ks->q1 = q1_off;
    ks->q2 = q2_off;
    ks->q3 = q3_off;
}

bool calc_ik( Kinematics* ks, double x, double y, double z)
{
    double q1, q2, q3;
    double r1, r2, r3, phi1, phi2;

    double l1 = ks->l1;     // base to q2
    double l2 = ks->l2;     // q2 to q3
    double l3 = ks->l3;    // q3 to efector
    double l4 = ks->l4;     // right shift
    double l5 = ks->l5;     // efector height

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

    ks->q1 = ks->q1_off + q1;
    ks->q2 = ks->q2_off + q2;
    ks->q3 = ks->q3_off + q3;

    ks->x = x;
    ks->y = y;
    ks->z = z;

    return true;
}

void calc_fk(Kinematics* ks, double q1, double q2, double q3)
{
    double l1 = ks->l1;     // base to q2
    double l2 = ks->l2;     // q2 to q3 
    double l3 = ks->l3;    // q3 to efector
    double l4 = ks->l4;     // right shift
    double l5 = ks->l5;     // efector height
    
    q1 -= ks->q1_off;
    q2 -= ks->q2_off;
    q3 -= ks->q3_off;

    ks->ax = -l2*sin(q2)*cos(q1) + l3*cos(q1)*cos(q2 + q3) + l4*sin(q1);
    ks->ay = -l2*sin(q1)*sin(q2) + l3*sin(q1)*cos(q2 + q3) - l4*cos(q1);
    ks->az = l1 + l2*cos(q2) + l3*sin(q2 + q3);
    ks->az -= l5;
}

int main()
{
    Kinematics ks;
    Kinematics_Init(&ks, L1, L2, L3, L4, L5, deg2rad(Q1_OFF), deg2rad(Q2_OFF), deg2rad(Q3_OFF));

    bool status = calc_ik(&ks, 120, -20, 0 );

    if( status )
    {
        printf("\nTARGET:\n");
        printf("X: %.2f \n", ks.x);
        printf("Y: %.2f \n", ks.y);
        printf("Z: %.2f \n", ks.z);

        printf("\nINVERSE KINEMATICS:\n");
        printf("Q1: %.8f deg, %d\n", rad2deg(ks.q1), rad2srv(ks.q1));
        printf("Q2: %.8f deg, %d\n", rad2deg(ks.q2), rad2srv(ks.q2));
        printf("Q3: %.8f deg, %d\n", rad2deg(ks.q3), rad2srv(ks.q3));

        calc_fk(&ks, ks.q1, ks.q2, ks.q3 );
        printf("\nFORWARD KINEMATICS from above:\n");
        printf("X: %.2f \n", ks.ax);
        printf("Y: %.2f \n", ks.ay);
        printf("Z: %.2f \n", ks.az);
    } 
    else
    {
        printf("\nSOLVER ERROR :(\n");
    }

    return 0;
}