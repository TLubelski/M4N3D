#include "pad.h"


volatile uint16_t adc_data[4];
PadState_t PAD;

void PAD_Init(ADC_HandleTypeDef* hadc)
{
	HAL_ADCEx_Calibration_Start(hadc, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(hadc, (uint32_t*)adc_data, 4);
	PAD.axis_L_X = 0;
	PAD.axis_L_Y = 0;
	PAD.axis_R_X = 0;
	PAD.axis_R_Y = 0;
	PAD.btn_L_short = false;
	PAD.btn_L_long = false;
	PAD.btn_R_short = false;
	PAD.btn_R_long = false;
	PAD.btn_combo_short = false;
	PAD.btn_combo_long = false;
}

// SUPREME ULTIMATE MULTI BUTTON SHORT N LONG PRESS DEBOUNCING ALGORITHM
void PAD_updateState()
{
	// get actual time
	uint32_t now = HAL_GetTick();

	static uint32_t last_lb = 0;
	static uint32_t last_end_lb = 0;
	static bool last_end_long_lb = false;
	static bool hold_lb = false;
	static bool hold_long_lb = false;
	uint8_t raw_lb;

	static uint32_t last_rb = 0;
	static uint32_t last_end_rb = 0;
	static bool last_end_long_rb = false;
	static bool hold_rb = false;
	static bool hold_long_rb = false;
	uint8_t raw_rb;

	static uint32_t last_combo = 0;


	// ##### HANDLE ADC #####
	static uint32_t last_adc = 0;
	if( now-last_adc > ADC_INTERVAL )
	{
		if( hold_lb || hold_long_lb || hold_rb || hold_long_rb)
		{
			PAD.axis_L_X = 0;
			PAD.axis_L_Y = 0;
			PAD.axis_R_X = 0;
			PAD.axis_R_Y = 0;
		}
		else
		{
			PAD.axis_L_X = ((4095-adc_data[1])-2048)/200;
			PAD.axis_L_Y = ((4095-adc_data[0])-2048)/200;
			PAD.axis_R_X = ((4095-adc_data[3])-2048)/200;
			PAD.axis_R_Y = ((4095-adc_data[2])-2048)/200;
		}
		last_adc = now;
	}

	// #### TURN OFF FLAGS
	if(PAD.btn_L_short) PAD.btn_L_short = false;
	if(PAD.btn_L_long) PAD.btn_L_long = false;
	if(PAD.btn_R_short) PAD.btn_R_short = false;
	if(PAD.btn_R_long) PAD.btn_R_long = false;
	if(PAD.btn_combo_short) PAD.btn_combo_short = false;
	if(PAD.btn_combo_long) PAD.btn_combo_long = false;


	// ##### HANDLE LEFT BUTTON #####
	raw_lb = !HAL_GPIO_ReadPin(PAD_L_SW_GPIO_Port, PAD_L_SW_Pin);

	if( raw_lb && !hold_lb && now-last_end_lb > DEBOUNCE)
	{
		hold_lb = true;
		last_lb = now;
	}

	if( hold_lb && now-last_lb > DEBOUNCE)
	{
		if( now-last_lb > LONG_PRESS )
		{
			if( !hold_long_lb )
			{
				if(now-last_combo > DEAD_TIME)
				{
					if( hold_long_rb )
					{
						PAD.btn_combo_long = true;
						last_combo = now;
					}
					else if( !hold_rb )
						PAD.btn_L_long = true;
				}
				hold_long_lb = true;
			}
			else if( !raw_lb )
			{
				hold_lb = false;
				hold_long_lb = false;
				last_end_lb = now;
				last_end_long_lb = true;
			}
		}
		else if( !raw_lb )
		{
			if(now-last_combo > DEAD_TIME)
			{
				if( (hold_rb && !hold_long_rb) || (!last_end_long_rb && now-last_end_rb < DEBOUNCE ))
				{
					PAD.btn_combo_short = true;
					last_combo = now;
				}
				else
					PAD.btn_L_short = true;
			}
			hold_lb = false;
            last_end_lb = now;
            last_end_long_lb = false;
		}
	}


	// ##### HANDLE RIGHT BUTTON #####
	raw_rb = !HAL_GPIO_ReadPin(PAD_R_SW_GPIO_Port, PAD_R_SW_Pin);

	if( raw_rb && !hold_rb && now-last_end_rb > DEBOUNCE)
	{
		hold_rb = true;
		last_rb = now;
	}

	if( hold_rb && now-last_rb > DEBOUNCE)
	{
		if( now-last_rb > LONG_PRESS )
		{
			if( !hold_long_rb )
			{
				if(now-last_combo > DEAD_TIME)
				{
					if( hold_long_lb )
					{
						PAD.btn_combo_long = true;
						last_combo = now;
					}
					else if( !hold_lb )
						PAD.btn_R_long = true;
				}
				hold_long_rb = true;
			}
			else if( !raw_rb )
			{
				hold_rb = false;
				hold_long_rb = false;
				last_end_rb = now;
				last_end_long_rb = true;
			}
		}
		else if( !raw_rb )
		{
			if(now-last_combo > DEAD_TIME)
			{
				if( (hold_lb && !hold_long_lb) || (!last_end_long_lb && now-last_end_lb < DEBOUNCE ))
				{
					PAD.btn_combo_short = true;
					last_combo = now;
				}
				else
					PAD.btn_R_short = true;
			}
            hold_rb = false;
            last_end_rb = now;
            last_end_long_rb = false;
		}
	}

	//#### COMBO MASKING SINGLE #####
	if( PAD.btn_combo_short || PAD.btn_combo_long )
	{
		PAD.btn_L_short = false;
		PAD.btn_L_long = false;
		PAD.btn_R_short = false;
		PAD.btn_R_long = false;
	}

}

inline void PAD_setLedManual(bool state) { HAL_GPIO_WritePin(LED_MANUAL_GPIO_Port, LED_MANUAL_Pin, state); }

inline void PAD_setLedFx(bool state) { HAL_GPIO_WritePin(LED_EFFECTOR_GPIO_Port, LED_EFFECTOR_Pin, state); }

