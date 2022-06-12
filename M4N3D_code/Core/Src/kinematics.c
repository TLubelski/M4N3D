#include "kinematics.h"

KS_Params_t KS_Params;

// CONVERTERS
double deg2rad(double deg) { return (deg/180.0f) * M_PI; }
double rad2deg(double rad) { return rad * (180.0f / M_PI); }
uint16_t rad2srv(double rad) { return (rad/M_PI)*512 + 512; }
uint16_t deg2srv(double deg) { return (deg/180.0f)*512 + 512; }
double srv2rad(uint16_t srv) { return (((double)srv-512.0f)/512.0f)*M_PI; }
double srv2deg(uint16_t srv) { return (((double)srv-512.0f)/512.0f)*180.0f; }

void KS_InitParams()
{
	KS_Params.set_reached = false;
	KS_Params.target_reached = false;
	KS_Params.fxState = 0;
}

// KINEMMATICS MATH
bool KS_calc_IK(double x, double y, double z)
{
    double q1, q2, q3;
    double r1, r2, r3, phi1, phi2;
    double _x, _y, _z;
    _x = x;
    _y = y;
    _z = z;

    //from user frame
    x *= (-1);
    x += FRAME_X;
    y *= (-1);
    y += FRAME_Y;

    //inverse kinematics
    q1 = 2 * atan( (x - sqrt( x*x + y*y - L4*L4 )) / ( L4-y ) );
    r1 = sqrt( x*x + pow( y+L4/cos(q1), 2) ) - L4*tan(q1);
    r2 = z - L1 + L5;
    r3 = sqrt( r1*r1 + r2*r2 );
    phi1 = atan( r2 / r1 );
    phi2 = M_PI/2 - phi1;
    q2 = acos( ( L3*L3 - L2*L2 - r3*r3 ) / (-2*L2*r3) ) - phi2;
    q3 = acos( ( r3*r3 - L2*L2 - L3*L3 ) / (-2*L2*L3) ) - M_PI/2;

    //check for NaN
    if(q1 != q1 || q2 != q2 || q3 != q3)
        return false;

    //offset
    KS_Params.s_q1 = deg2rad(Q1_OFF) + q1;
    KS_Params.s_q2 = deg2rad(Q2_OFF) + q2;
    KS_Params.s_q3 = deg2rad(Q3_OFF) + q3;

    KS_Params.s_x = _x;
    KS_Params.s_y = _y;
    KS_Params.s_z = _z;


    return true;
}

void KS_calc_FK()
{
	//offset
    double q1 = KS_Params.a_q1 - deg2rad(Q1_OFF);
    double q2 = KS_Params.a_q2 - deg2rad(Q2_OFF);
    double q3 = KS_Params.a_q3 - deg2rad(Q3_OFF);

    //forward kinematics
    KS_Params.a_x = -L2*sin(q2)*cos(q1) + L3*cos(q1)*cos(q2 + q3) + L4*sin(q1);
    KS_Params.a_y = -L2*sin(q1)*sin(q2) + L3*sin(q1)*cos(q2 + q3) - L4*cos(q1);
    KS_Params.a_z = L1 + L2*cos(q2) + L3*sin(q2 + q3) - L5;

    //to user frame
    KS_Params.a_x -= FRAME_X;
    KS_Params.a_x *= (-1);
    KS_Params.a_y -= FRAME_Y;
    KS_Params.a_y *= (-1);
}

static inline void KS_setTarget(double x, double y, double z)
{
	KS_Params.t_x = x;
	KS_Params.t_y = y;
	KS_Params.t_z = z;
}

// MANAGERS
void KS_getActualPos()
{
	static uint32_t last_get = 0;
	uint32_t now = HAL_GetTick();

	if(now-last_get > UPDATE_INTERVAL)
	{
		KS_Params.a_q1 = srv2rad(SRV_readPosition(1));
		KS_Params.a_q2 = srv2rad(SRV_readPosition(2));
		KS_Params.a_q3 = srv2rad(SRV_readPosition(3));
		KS_calc_FK();
		KS_Params.set_reached = ( fabs(KS_Params.s_x - KS_Params.a_x) < THRESHOLD_L &&
				 	 	 	 	  fabs(KS_Params.s_y - KS_Params.a_y) < THRESHOLD_L &&
								  fabs(KS_Params.s_z - KS_Params.a_z) < THRESHOLD_L );
		KS_Params.target_reached = ( fabs(KS_Params.t_x - KS_Params.a_x) < THRESHOLD_L &&
				 	 	 	 	 	 fabs(KS_Params.t_y - KS_Params.a_y) < THRESHOLD_L &&
									 fabs(KS_Params.t_z - KS_Params.a_z) < THRESHOLD_L );
		last_get = now;
	}
}

void KS_setPos(double x, double y, double z)
{
	if( KS_calc_IK(x, y, z) )
	{
		SRV_move(1, rad2srv(KS_Params.s_q1), SPEED+20);
		SRV_move(2, rad2srv(KS_Params.s_q2), SPEED);
		SRV_move(3, rad2srv(KS_Params.s_q3), SPEED);
	}
	else
		CTRL_changeState(HALT);
}



void KS_movementLoop()
{
	double x, y, z, len;
	if( !KS_Params.target_reached )
	{
		if( KS_Params.set_reached )
		{
			x = KS_Params.t_x - KS_Params.s_x;
			y = KS_Params.t_y - KS_Params.s_y;
			z = KS_Params.t_z - KS_Params.s_z;
			len = sqrt( x*x + y*y + z*z );
			if( len > 1 )
			{
				x = KS_Params.s_x + (x/len)*STEP_L;
				y = KS_Params.s_y + (y/len)*STEP_L;
				z = KS_Params.s_z + (z/len)*STEP_L;
			}
			else
			{
				x = KS_Params.t_x;
				y = KS_Params.t_y;
				z = KS_Params.t_z;
			}
			KS_setPos(x, y, z);
		}
	}
}


void KS_moveJ(double x, double y, double z)
{
	KS_Params.target_reached = false;
	KS_Params.set_reached = false;
	KS_setTarget(x, y, z);
	KS_setPos(x, y, z);
}

void KS_moveL(double x, double y, double z)
{
	KS_Params.target_reached = false;
	KS_Params.set_reached = false;
	KS_setTarget(x, y, z);
}


void KS_moveByVector(double x, double y, double z)
{
	KS_moveL(KS_Params.t_x+x/2, KS_Params.t_y+y/2, KS_Params.t_z+z/3);
}

void KS_goHome()
{
	KS_moveJ(HOME_X, HOME_Y, HOME_Z);
}

void KS_setFx(uint8_t state)
{
	KS_Params.fxState = state;
	HAL_GPIO_WritePin(EFFECTOR_GPIO_Port, EFFECTOR_Pin, state);
	PAD_setLedFx(state);
}


