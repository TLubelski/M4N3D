#include "control.h"

MoveVect_t MoveVect;
RobotParams_t RobotParams;
CommandParms_t CommandParams;


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
    RobotParams.mode = MANUAL;

    MoveVect.x = 0;
    MoveVect.y = 0;
    MoveVect.z = 0;
}


void CTRL_setFx(uint8_t state)
{
	RobotParams.fxState = state;
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
	SRV_move(1, rad2srv(RobotParams.q1), SPEED);
	SRV_move(2, rad2srv(RobotParams.q2), SPEED);
	SRV_move(3, rad2srv(RobotParams.q3), SPEED);
}

bool CTRL_destinationReached()
{
	return ( fabs(RobotParams.q1-RobotParams.aq1) < deg2rad(THRESHOLD_J) &&
			 fabs(RobotParams.q2-RobotParams.aq2) < deg2rad(THRESHOLD_J) &&
			 fabs(RobotParams.q3-RobotParams.aq3) < deg2rad(THRESHOLD_J) );
}


void CTRL_setPos(double x, double y, double z)
{
	if(KS_calc_IK(x, y, z))
		CTRL_pushTargetParams();
	else
		printf("Inverse kinematics error");
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

void CTRL_printInfo()
{
	static uint32_t last_print = 0;
	uint32_t now = HAL_GetTick();

	if( now-last_print > INFO_INTERVAL )
	{
		COM_sendInfo(RobotParams.ax, RobotParams.ay, RobotParams.az, RobotParams.aq1, RobotParams.aq2, RobotParams.aq3, RobotParams.fxState);
		last_print = now;
	}
}

void CTRL_parseCommand()
{
	HAL_Delay(1);
	switch(COM_data.cmd)
	{
	case CMD_START:
		PAD_setLedManual(0);
		RobotParams.mode = PROGRAM;
		CommandParams.type = IDLE;
		COM_sendDone();
		break;

	case CMD_STOP:
		PAD_setLedManual(1);
		RobotParams.mode = MANUAL;
		COM_sendDone();
		break;

	case CMD_MOVE_J:
		CommandParams.type = MOVING_J;
		CommandParams.x = COM_data.f_param1;
		CommandParams.y = COM_data.f_param2;
		CommandParams.z = COM_data.f_param3;
		CTRL_setPos(CommandParams.x, CommandParams.y, CommandParams.z);
		break;

	case CMD_MOVE_L:
		CommandParams.type = MOVING_L;
		CommandParams.x = COM_data.f_param1;
		CommandParams.y = COM_data.f_param2;
		CommandParams.z = COM_data.f_param3;
		CTRL_setPos(CommandParams.x, CommandParams.y, CommandParams.z);
		break;

	case CMD_WAIT:
		CommandParams.type = WAIT;
		CommandParams.start = HAL_GetTick();
		CommandParams.timer = COM_data.u32_param;
		break;

	case CMD_MAGNET:
		CTRL_setFx(COM_data.u8_param);
		COM_sendDone();
		break;
	}

	COM_data.available = 0;
}

void CTRL_Loop()
{
	if(COM_data.available)
		CTRL_parseCommand();

	if(RobotParams.mode == MANUAL)
	{
		CTRL_getMoveVect();

		if( PAD.btn_combo_short )
			CTRL_setFx(!RobotParams.fxState);

		if( PAD.btn_combo_long )
			CTRL_setPos(134, -33, 88);

		if( CTRL_destinationReached() )
		{
			CTRL_moveByVect();
		}
	}
	else if(RobotParams.mode == PROGRAM)
	{
		switch( CommandParams.type )
		{
		case IDLE:
			break;

		case WAIT:
			if( HAL_GetTick()-CommandParams.start > CommandParams.timer )
			{
				CommandParams.type = IDLE;
				COM_sendDone();
			}
			break;

		case MOVING_J:
			if( CTRL_destinationReached() )
			{
				CommandParams.type = IDLE;
				COM_sendDone();
			}
			break;

		case MOVING_L:
			if( CTRL_destinationReached() )
			{
				CommandParams.type = IDLE;
				COM_sendDone();
			}
			break;
		}
	}
}

