#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "control.h"
#include "servo.h"
#include "pad.h"
#include "comm.h"

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#define UPDATE_INTERVAL 10

#define L1 44.5 	// base to q2
#define L2 83.2 	// q2 to q3
#define L3 136.3 	// q3 to efector
#define L4 31.75 	// right shift
#define L5 37.6 	// efector height
#define Q1_OFF 0
#define Q2_OFF 16
#define Q3_OFF -5

#define FRAME_X 105
#define FRAME_Y 5

#define HOME_X 0
#define HOME_Y 0
#define HOME_Z 100

#define SPEED 50
#define STEP_L 3

#define THRESHOLD_L 6


typedef struct{
    //actual values
    double a_q1, a_q2, a_q3;
    double a_x, a_y, a_z;

    //set values
    double s_q1, s_q2, s_q3;
    double s_x, s_y, s_z;

    //target values
    double t_x, t_y, t_z;

    bool set_reached;
    bool target_reached;

    uint8_t fxState;
} KS_Params_t;

extern KS_Params_t KS_Params;

double deg2rad(double deg);
double rad2deg(double rad);
uint16_t rad2srv(double rad);
uint16_t deg2srv(double deg);
double srv2rad(uint16_t srv);
double srv2deg(uint16_t srv);

void KS_InitParams();
bool KS_calc_IK(double x, double y, double z);
void KS_calc_FK();

void KS_getActualPos();
void KS_setPos(double x, double y, double z);

void KS_movementLoop();
void KS_moveL(double x, double y, double z);
void KS_moveJ(double x, double y, double z);
void KS_moveByVector(double x, double y, double z);
void KS_goHome();

void KS_setFx(uint8_t state);

#endif
