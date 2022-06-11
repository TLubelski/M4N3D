#ifndef CONTROL_H
#define CONTROL_H

#include "main.h"
#include "servo.h"
#include "pad.h"
#include "comm.h"
#include "kinematics.h"
#include <stdbool.h>

#define GETREAL_INTERVAL 10
#define INFO_INTERVAL 1000
#define SPEED 35
#define THRESHOLD_J 5
#define THRESHOLD_L 2

typedef struct{
	double x, y, z;
} MoveVect_t;

extern MoveVect_t MoveVect;

typedef enum {MANUAL, PROGRAM}CTRL_Mode_t;
typedef enum {IDLE, MOVING_J, MOVING_L, WAIT}CTRL_MoveType_t;

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
    // fx
    bool fxState;
    // mode
    CTRL_Mode_t mode;


} RobotParams_t;

typedef struct{
	CTRL_MoveType_t type;
	float x;
	float y;
	float z;
	float step_x;
	float step_y;
	float step_z;
	uint32_t start;
	uint32_t timer;
} CommandParms_t;


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
void CTRL_printInfo();
void CTRL_Loop();

#endif
