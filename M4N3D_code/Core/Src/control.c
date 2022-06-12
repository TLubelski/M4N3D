#include "control.h"

CTRL_StateMachine_t stateMachine;
CTRL_CommandParams_t CommandParams;

uint32_t CMD_TIMEOUT = 10000;
uint32_t HALT_TIMEOUT = 10000;

/* ###############################
 *         STARTUP
 * ###############################
 */
void CTRL_startup()
{
	stateMachine.stateChanged = false;
	stateMachine.state = MANUAL;

	PAD_setLedManual(LED_ON);
	for(uint8_t i = 1; i <=3; i++)
	{
		SRV_setLED(i, 1);
		SRV_enableTorque(i, 1);
	}
	KS_goHome();
	print("System started");
}

/* ###############################
 *         COMMUNICATION
 * ###############################
 */
void CTRL_printInfo()
{
	static uint32_t last_print = 0;
	uint32_t now = HAL_GetTick();

	if( now-last_print > INFO_INTERVAL )
	{
		COM_sendInfo(KS_Params.a_x, KS_Params.a_y, KS_Params.a_z, rad2deg(KS_Params.a_q1), rad2deg(KS_Params.a_q2), rad2deg(KS_Params.a_q3), KS_Params.fxState);
		last_print = now;
	}
}

/* ###############################
 *         STATE MANAGMENT
 * ###############################
 */
void CTRL_changeState(CTRL_State_t state)
{
	stateMachine.newState = state;
	stateMachine.stateChanged = true;
}

void CTRL_stateChangeHandler()
{
	switch(stateMachine.newState)
	{
	case HALT:
		print("Failed to calculate inverse kinematics. HALT!");
		PAD_setLedManual(LED_BLINK);
		break;

	case MANUAL:
		PAD_setLedManual(LED_ON);
		KS_setFx(0);
		break;

	case PROGRAM:
		PAD_setLedManual(LED_OFF);
		CommandParams.type = IDLE;
		KS_setFx(0);
		break;
	}
	stateMachine.state = stateMachine.newState;
	stateMachine.stateChanged = false;
}


/* ###############################
 *         COMMAND MANAGMENT
 * ###############################
 */
void CTRL_parseCommand()
{
	switch(COM_data.cmd)
	{
	case CMD_START:
		CTRL_changeState(PROGRAM);
		COM_sendDone();
		break;

	case CMD_STOP:
		CTRL_changeState(MANUAL);
		COM_sendDone();
		break;

	case CMD_MOVE_J:
		CommandParams.type = MOVING_J;
		CommandParams.start = HAL_GetTick();
		KS_moveJ(COM_data.f_param1, COM_data.f_param2, COM_data.f_param3);
		break;

	case CMD_MOVE_L:
		CommandParams.type = MOVING_L;
		CommandParams.start = HAL_GetTick();
		KS_moveL(COM_data.f_param1, COM_data.f_param2, COM_data.f_param3);
		break;

	case CMD_WAIT:
		CommandParams.type = WAIT;
		CommandParams.start = HAL_GetTick();
		CommandParams.timer = COM_data.u32_param;
		break;

	case CMD_MAGNET:
		KS_setFx(COM_data.u8_param);
		COM_sendDone();
		break;
	}

	COM_data.available = 0;
}

/* ###############################
 *     MAIN MOVEMENT CONTROL
 * ###############################
 */
void CTRL_Loop()
{
	uint32_t now = HAL_GetTick();

	if(stateMachine.stateChanged)
		CTRL_stateChangeHandler();

	if(COM_data.available)
		CTRL_parseCommand();

	if(stateMachine.state == MANUAL)
	{
		if( PAD.btn_combo_short )
			KS_setFx(!KS_Params.fxState);

		if( PAD.btn_combo_long )
			KS_goHome();

		if( KS_Params.target_reached )
		{
			KS_moveByVector(PAD.axis_R_X, PAD.axis_R_Y, PAD.axis_L_Y);
		}
		KS_movementLoop();
	}
	else if(stateMachine.state == PROGRAM)
	{
		switch( CommandParams.type )
		{
		case IDLE:
			break;

		case WAIT:
			if( now-CommandParams.start > CommandParams.timer )
			{
				CommandParams.type = IDLE;
				COM_sendDone();
			}
			break;

		case MOVING_L:
		case MOVING_J:
			if( KS_Params.target_reached || now-CommandParams.start > CMD_TIMEOUT )
			{
				CommandParams.type = IDLE;
				COM_sendDone();
			}
			KS_movementLoop();
			break;
		}

	}
	else if(stateMachine.state == HALT)
	{
		if( PAD.btn_combo_long )
		{
			print("Resetting position to home");
			KS_goHome();
			CTRL_changeState(MANUAL);
		}

	}
}

