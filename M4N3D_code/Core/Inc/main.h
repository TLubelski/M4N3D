/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ADC11_L_X_Pin GPIO_PIN_0
#define ADC11_L_X_GPIO_Port GPIOC
#define ADC12_L_Y_Pin GPIO_PIN_1
#define ADC12_L_Y_GPIO_Port GPIOC
#define ADC13_R_X_Pin GPIO_PIN_2
#define ADC13_R_X_GPIO_Port GPIOC
#define ADC14_R_Y_Pin GPIO_PIN_3
#define ADC14_R_Y_GPIO_Port GPIOC
#define TTY_UART_TX_Pin GPIO_PIN_2
#define TTY_UART_TX_GPIO_Port GPIOA
#define TTY_UART_RX_Pin GPIO_PIN_3
#define TTY_UART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define EFFECTOR_Pin GPIO_PIN_4
#define EFFECTOR_GPIO_Port GPIOC
#define LED_MANUAL_Pin GPIO_PIN_6
#define LED_MANUAL_GPIO_Port GPIOC
#define LED_EFFECTOR_Pin GPIO_PIN_7
#define LED_EFFECTOR_GPIO_Port GPIOC
#define PAD_R_SW_Pin GPIO_PIN_8
#define PAD_R_SW_GPIO_Port GPIOC
#define PAD_L_SW_Pin GPIO_PIN_9
#define PAD_L_SW_GPIO_Port GPIOC
#define SRV_UART_RXTX_Pin GPIO_PIN_9
#define SRV_UART_RXTX_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
