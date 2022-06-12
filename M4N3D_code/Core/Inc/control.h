#ifndef CONTROL_H
#define CONTROL_H

#include "main.h"
#include "servo.h"
#include "pad.h"
#include "comm.h"
#include "kinematics.h"
#include <stdbool.h>


#define INFO_INTERVAL 100



typedef enum {HALT, MANUAL, PROGRAM}CTRL_State_t;
typedef struct{
	CTRL_State_t state;
	CTRL_State_t newState;
	bool stateChanged;
	uint32_t start;
}CTRL_StateMachine_t;


typedef enum {IDLE, MOVING_J, MOVING_L, WAIT}CTRL_MoveType_t;
typedef struct{
	CTRL_MoveType_t type;
	uint32_t start;
	uint32_t timer;
} CTRL_CommandParams_t;

void CTRL_startup();
void CTRL_printInfo();
void CTRL_changeState(CTRL_State_t state);
void CTRL_Loop();


#endif
