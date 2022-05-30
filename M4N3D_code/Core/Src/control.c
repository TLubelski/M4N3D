#include "control.h"

MoveVect_t MoveVect;
RobotParams_t RobotParams;

void RobotParams_Init(double l1, double l2, double l3, double l4, double l5, double q1_off, double q2_off, double q3_off )
{
    RobotParams.l1 = l1;     // base to q2
    RobotParams.l2 = l2;     // q2 to q3
    RobotParams.l3 = l3;     // q3 to efector
    RobotParams.l4 = l4;     // right shift
    RobotParams.l5 = l5;     // efector height

    RobotParams.q1_off = q1_off;
    RobotParams.q2_off = q2_off;
    RobotParams.q3_off = q3_off;

    RobotParams.q1 = q1_off;
    RobotParams.q2 = q2_off;
    RobotParams.q3 = q3_off;

    RobotParams.fxState = false;

    MoveVect.x = 0;
    MoveVect.y = 0;
    MoveVect.z = 0;
}


void toggleFx()
{
	RobotParams.fxState = !RobotParams.fxState;
	HAL_GPIO_WritePin(EFFECTOR_GPIO_Port, EFFECTOR_Pin, RobotParams.fxState);
	PAD_setLedFx(RobotParams.fxState);
}

void CTRL_getMoveVect()
{
	MoveVect.x = (-PAD.axis_R_X)/10;
	MoveVect.y = (-PAD.axis_R_Y)/10;
	MoveVect.z = (PAD.axis_L_Y)/10;
}

void CTRL_getRealParams()
{
	static uint32_t last_get = 0;
	uint32_t now = HAL_GetTick();

	if(now-last_get > GETREAL_INTERVAL)
	{
		RobotParams.aq1 = srv2rad(SRV_readPosition(1));
		RobotParams.aq2 = srv2rad(SRV_readPosition(2));
		RobotParams.aq3 = srv2rad(SRV_readPosition(3));
		KS_calc_FK();
		last_get = now;
	}
}

void CTRL_pushTargetParams()
{
	SRV_move(1, rad2srv(RobotParams.q1), MANUAL_SPEED);
	SRV_move(2, rad2srv(RobotParams.q2), MANUAL_SPEED);
	SRV_move(3, rad2srv(RobotParams.q3), MANUAL_SPEED);
}

bool CTRL_destinationReached_J()
{
	return ( fabs(RobotParams.q1-RobotParams.aq1) < THRESHOLD_J &&
			 fabs(RobotParams.q2-RobotParams.aq2) < THRESHOLD_J &&
			 fabs(RobotParams.q3-RobotParams.aq3) < THRESHOLD_J    );
}

bool CTRL_destinationReached_L()
{
	return ( fabs(RobotParams.x-RobotParams.ax) < THRESHOLD_L &&
			 fabs(RobotParams.y-RobotParams.ay) < THRESHOLD_L &&
			 fabs(RobotParams.z-RobotParams.az) < THRESHOLD_L    );
}

void CTRL_setPos(double x, double y, double z)
{
	if(KS_calc_IK(x, y, z))
		CTRL_pushTargetParams();
	else
		printf("Inverse kinematics error\r\n");
}

void CTRL_startup()
{
	PAD_setLedManual(1);

	for(uint8_t i = 1; i <=3; i++)
	{
		SRV_setLED(i, 1);
		SRV_enableTorque(i, 1);
	}

	CTRL_setPos(134, -33, 88);
}

void CTRL_moveByVect()
{
	if( MoveVect.x != 0 || MoveVect.y != 0 || MoveVect.z != 0 )
		CTRL_setPos(RobotParams.x+MoveVect.x, RobotParams.y+MoveVect.y, RobotParams.z+MoveVect.z);
}


void CTRL_Loop_Manual()
{
	static uint32_t last_print = 0;
	uint32_t now = HAL_GetTick();

	if( now-last_print > 100 )
	{
		printf("#PAD RX: %d, RY: %d, LX: %d, LY: %d\r\n", PAD.axis_R_X, PAD.axis_R_Y, PAD.axis_L_X, PAD.axis_L_Y);
		printf("#VECT X: %.2f, Y: %.2f, Z: %.2f\r\n", MoveVect.x, MoveVect.y, MoveVect.z);
		printf("#TARGET: Q1: %.2f, Q1: %.2f, Q1: %.2f, X: %.2f, Y: %.2f, Z: %.2f\r\n", RobotParams.q1, RobotParams.q2, RobotParams.q3, RobotParams.x, RobotParams.y, RobotParams.z);
		printf("#ACTUAL: Q1: %.2f, Q1: %.2f, Q1: %.2f, X: %.2f, Y: %.2f, Z: %.2f\r\n", RobotParams.aq1, RobotParams.aq2, RobotParams.aq3, RobotParams.ax, RobotParams.ay, RobotParams.az);

		last_print = now;
	}

	if( PAD.btn_combo_short )
		toggleFx();


	CTRL_getMoveVect();
	if( CTRL_destinationReached_J() )
	{
		CTRL_moveByVect();
	}
}

