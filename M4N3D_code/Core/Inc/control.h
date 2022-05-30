#ifndef CONTROL_H
#define CONTROL_H

#include "main.h"
#include "servo.h"
#include "pad.h"
#include "kinematics.h"
#include <stdbool.h>

#define GETREAL_INTERVAL 10
#define MANUAL_SPEED 35
#define THRESHOLD_J 3
#define THRESHOLD_L 2

typedef struct{
	double x, y, z;
} MoveVect_t;

extern MoveVect_t MoveVect;

typedef struct{
	//params
    double l1, l2, l3, l4, l5;
    double q1_off, q2_off, q3_off;
    //targets
    double x, y, z;
    double q1, q2, q3;
    //actual values
    double aq1, aq2, aq3;
    double ax, ay, az;
    //
    bool fxState;
} RobotParams_t;

extern RobotParams_t RobotParams;

void RobotParams_Init(double l1, double l2, double l3, double l4, double l5, double q1_off, double q2_off, double q3_off);
void CTRL_getMoveVect();
void CTRL_getRealParams();
void CTRL_pushTargetParams();
bool CTRL_destinationReached_J();
bool CTRL_destinationReached_L();
void CTRL_setPos(double x, double y, double z);
void CTRL_startup();
void CTRL_moveByVect();
void CTRL_Loop_Manual();

#endif
