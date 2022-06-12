#ifndef COMM_H
#define COMM_H

#include "main.h"


#define UART_TIMEOUT 50
#define COM_RX_BUFF_SIZE 255

typedef enum {CMD_START = 1, CMD_STOP = 2,  CMD_MOVE_L = 3, CMD_MOVE_J = 4, CMD_WAIT = 5, CMD_MAGNET = 6} RxCommand_t;
typedef enum {COM_ACK = 11, COM_DONE = 12, COM_INFO = 13, COM_MSG = 14 } TxPacket_t;

typedef struct {
	uint8_t available;
	RxCommand_t cmd;
	float f_param1;
	float f_param2;
	float f_param3;
	uint32_t u32_param;
	uint8_t u8_param;
}COM_Data_t;

extern volatile COM_Data_t COM_data;

void COM_Init(UART_HandleTypeDef* huart);
void COM_uartIRQ(UART_HandleTypeDef* huart);
void COM_rxLoop();
void COM_sendDone();
void COM_sendPacket(uint8_t* data, uint8_t d_len);
void COM_sendInfo(float x, float y, float z, float q1, float q2, float q3, uint8_t magnet);
void COM_sendMsg(const char* msg);
void print(const char *fmt, ...);

#endif
