#ifndef PAD_H
#define PAD_H

#include "main.h"
#include <stdbool.h>

#define ADC_INTERVAL 0
#define LONG_PRESS 1500
#define DEBOUNCE 20
#define DEAD_TIME 500
#define BLINK_TIME 200

typedef enum { LED_OFF=0, LED_ON=1, LED_BLINK=2 } LED_State_t;


typedef struct{
	int16_t axis_L_X;
	int16_t axis_L_Y;
	int16_t axis_R_X;
	int16_t axis_R_Y;
	bool btn_L_short;
	bool btn_R_short;
	bool btn_L_long;
	bool btn_R_long;
	bool btn_combo_short;
	bool btn_combo_long;
}PadState_t;

extern PadState_t PAD;

void PAD_Init(ADC_HandleTypeDef*);
void PAD_updateState();
void PAD_setLedManual(LED_State_t state);
void PAD_setLedFx(bool state);


#endif
