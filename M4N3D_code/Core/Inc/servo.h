#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"


void SRV_uartIRQ(UART_HandleTypeDef* huart);
void SRV_Init(UART_HandleTypeDef* huart);

uint8_t SRV_setLED(uint8_t id, uint8_t state);
uint8_t SRV_move(uint8_t id, uint16_t position, uint16_t speed);
uint8_t SRV_enableTorque(uint8_t id, uint8_t state);
uint16_t SRV_readPosition(uint8_t id);


#endif
