#include "servo.h"
#include "servo_defs.h"
#include <string.h>

//######################
//  UART COMMUNICATION
//######################

#define UART_TIMEOUT 50
UART_HandleTypeDef* huart_srv;

#define SRV_RX_BUFF_SIZE 16
volatile uint8_t SRV_RxBuff[SRV_RX_BUFF_SIZE];
volatile uint8_t* SRV_rx_head;
volatile uint8_t* SRV_rx_tail;


void SRV_uartClearBuff()
{
	SRV_rx_head = SRV_RxBuff;
	SRV_rx_tail = SRV_RxBuff;
}

static inline void SRV_uartStopRx()
{
	huart_srv->RxState = HAL_UART_STATE_READY;
}

static inline void SRV_uartStartRx()
{
	HAL_UART_Receive_IT(huart_srv, (uint8_t*)SRV_rx_head, 1);
}

void SRV_uartIRQ(UART_HandleTypeDef* huart)
{
	if(huart == huart_srv)
	{
		SRV_rx_head++;
		if( SRV_rx_head == SRV_RxBuff+SRV_RX_BUFF_SIZE)
			SRV_rx_head = SRV_RxBuff;
		SRV_uartStartRx();
	}
}

uint8_t SRV_uartDataAvailable()
{
	return SRV_rx_head-SRV_rx_tail;
}

uint8_t SRV_uartReadByte()
{
	return *(SRV_rx_tail++);
}

uint8_t SRV_uartPeek()
{
	return *(SRV_rx_tail);
}

void SRV_uartSendPacket(uint8_t* packet, uint8_t len)
{
	SRV_uartStopRx();
	SRV_uartClearBuff();
	HAL_HalfDuplex_EnableTransmitter(huart_srv);
	HAL_UART_Transmit(huart_srv, packet , len, UART_TIMEOUT);
	HAL_HalfDuplex_EnableReceiver(huart_srv);
	SRV_uartStartRx();
}

/* #############################
 *   SERVO COMMUNICATION LAYER
 * #############################
 */
void SRV_sendCommand(uint8_t id, uint8_t* params)
{
	uint8_t base_len = 4;
	uint8_t params_len = params[0];
	uint8_t len = base_len + params_len;
	//preapare packet
	uint8_t packet[len];
	packet[0] = AX_START;
	packet[1] = AX_START;
	packet[2] = id;
	memcpy(packet+3, params, params_len);

	//calculate checksum
	uint8_t checksum = 0;
	for( uint8_t i = 2; i < len-1; i++)
		checksum += packet[i];
	checksum = ( ~checksum ) & 0xFF;
	packet[len-1] = checksum;

	//send via uart
	SRV_uartSendPacket(packet, len);
}

uint8_t SRV_getResponse(uint8_t* response, uint8_t len)
{
	uint32_t start = HAL_GetTick();
	//wait for data to arrive
	while( SRV_uartDataAvailable() < len )
	{
		if(HAL_GetTick()-start > UART_TIMEOUT) //fail when timed out
			return 1;
	}
	//check for start byte
	if( SRV_uartPeek() == AX_START )
	{
		//copy from rx buff
		for(uint8_t i = 0; i < len; i++)
			response[i] = SRV_uartReadByte();
		return 0;
	}
	else return 1;
}



/* ###############################
 *   SERVO ABSTRACT COMMANDS
 * ###############################
 */
void SRV_Init(UART_HandleTypeDef* huart)
{
	huart_srv = huart;
	SRV_uartClearBuff();
}

uint8_t SRV_readError()
{
	uint8_t response[5];
	SRV_getResponse(response, 5);
	return response[4];
}

uint8_t SRV_setLED(uint8_t id, uint8_t state)
{
	uint8_t cmd[] = { AX_LED_LENGTH, AX_WRITE_DATA, AX_LED, state};
	SRV_sendCommand(id, cmd);
	return SRV_readError();
}

uint8_t SRV_move(uint8_t id, uint16_t position, uint16_t speed)
{
    uint8_t Position_H = position >> 8;           // 16 bits - 2 x 8 bits variables
    uint8_t Position_L = position;
    uint8_t Speed_H = speed >> 8;
    uint8_t Speed_L = speed;                      // 16 bits - 2 x 8 bits variables

	uint8_t cmd[] = {AX_GOAL_SP_LENGTH, AX_WRITE_DATA, AX_GOAL_POSITION_L, Position_L, Position_H, Speed_L, Speed_H };
	SRV_sendCommand(id, cmd);
	return SRV_readError();
}

uint8_t SRV_enableTorque(uint8_t id, uint8_t state)
{
	uint8_t cmd[] = { AX_TORQUE_LENGTH, AX_WRITE_DATA, AX_TORQUE_ENABLE, state };
	SRV_sendCommand(id, cmd);
	return SRV_readError();
}

uint16_t SRV_readPosition(uint8_t id)
{
	uint8_t cmd[] = {AX_POS_LENGTH, AX_READ_DATA, AX_PRESENT_POSITION_L, AX_BYTE_READ_POS};
	SRV_sendCommand(id, cmd);

	uint8_t response[8];
	SRV_getResponse(response,8);
	return (response[6]<<8) + response[5];
}






