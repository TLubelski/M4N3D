#include "comm.h"
#include <stdio.h>
#include <string.h>

typedef union {
    float var;
    uint8_t bytes[4];
} floatArray;

typedef union {
    uint32_t var;
    uint8_t bytes[4];
} u32Array;

typedef enum {COM_IDLE, COM_START_CHECK, COM_LEN, COM_CHECKSUM, COM_DATA, COM_ENDL, COM_CPLT }COM_State_t;

volatile COM_State_t COM_state = COM_IDLE;
volatile COM_Data_t COM_data;
UART_HandleTypeDef* huart_com;
volatile uint8_t COM_data_len;
volatile uint8_t COM_RxBuff[COM_RX_BUFF_SIZE];
volatile uint8_t* COM_rx_head;


void COM_parsePacket();
void COM_sendACK();


void COM_clearBuff()
{
	COM_state = COM_IDLE;
	COM_rx_head = COM_RxBuff;
	COM_data_len = 0;
	HAL_UART_Receive_IT(huart_com, (uint8_t*)COM_rx_head, 1);
}

void COM_Init(UART_HandleTypeDef* huart)
{
	COM_data.available = 0;
	huart_com = huart;
	COM_clearBuff();
}

void COM_uartIRQ(UART_HandleTypeDef* huart)
{
	if(huart == huart_com)
	{
		switch(COM_state)
		{
		case COM_IDLE: //received 1st START
			if(COM_rx_head[0] == 0xFF)
			{
				COM_state = COM_START_CHECK;
				COM_rx_head++;
				HAL_UART_Receive_IT(huart_com, (uint8_t*)COM_rx_head, 1);
			}
			else
				COM_clearBuff();
			break;

		case COM_START_CHECK: //received 2nd START
			if(COM_RxBuff[1] == 0xFF)
			{
				COM_state = COM_LEN;
				COM_rx_head++;
				HAL_UART_Receive_IT(huart_com, (uint8_t*)COM_rx_head, 1);
			}
			else
				COM_clearBuff();

			break;

		case COM_LEN: //received LEN
			COM_state = COM_DATA;
			COM_data_len = COM_RxBuff[2];
			COM_rx_head++;
			HAL_UART_Receive_IT(huart_com, (uint8_t*)COM_rx_head, COM_data_len);
			break;

		case COM_DATA: //received DATA
			COM_state = COM_CHECKSUM;
			COM_rx_head += COM_data_len;
			HAL_UART_Receive_IT(huart_com, (uint8_t*)COM_rx_head, 1);
			break;

		case COM_CHECKSUM: //received CHECKSUM
			COM_state = COM_ENDL;
			COM_rx_head += COM_data_len;
			HAL_UART_Receive_IT(huart_com, (uint8_t*)COM_rx_head, 1);
			break;

		case COM_ENDL: //received \n
			COM_state = COM_CPLT;
			break;

		case COM_CPLT: //complete
			break;
		}
	}
}

void COM_rxLoop()
{
	if( COM_state == COM_CPLT)
	{
		uint8_t checksum = 0;
		for( uint8_t i = 2; i < COM_data_len-1; i++)
			checksum += COM_RxBuff[i];
		checksum = ( ~checksum ) & 0xFF;

//		if( checksum == COM_RxBuff[2+COM_data_len] )
		if(1)
		{
			COM_parsePacket();
			COM_data.available = 1;
			HAL_Delay(1);
			COM_sendACK();
		}
		COM_clearBuff();
	}
}

void COM_parsePacket()
{
	floatArray f_pool;
	u32Array i_pool;

	COM_data.cmd = COM_RxBuff[3];
	switch(COM_data.cmd)
	{
	case CMD_START:
	case CMD_STOP:
		break;

	case CMD_MOVE_L:
	case CMD_MOVE_J:
		memcpy( f_pool.bytes, (uint8_t*)COM_RxBuff+4, 4);
		COM_data.f_param1 = f_pool.var;
		memcpy( f_pool.bytes, (uint8_t*)COM_RxBuff+8, 4);
		COM_data.f_param2 = f_pool.var;
		memcpy( f_pool.bytes, (uint8_t*)COM_RxBuff+12, 4);
		COM_data.f_param3 = f_pool.var;
		break;

	case CMD_WAIT:
		memcpy( i_pool.bytes, (uint8_t*)COM_RxBuff+4, 4);
		COM_data.u32_param = i_pool.var;
		break;

	case CMD_MAGNET:
		COM_data.u8_param = COM_RxBuff[4];
		break;
	}
}

void COM_sendPacket(uint8_t* data, uint8_t d_len)
{
	uint8_t base_len = 5;
	uint8_t len = base_len + d_len;

	uint8_t packet[len];
	packet[0] = 0xFF;
	packet[1] = 0xFF;
	packet[2] = d_len;
	memcpy(packet+3, data, d_len);

	//calculate checksum
	uint8_t checksum = 0;
	for( uint8_t i = 2; i < len-2; i++)
		checksum += packet[i];
	checksum = ( ~checksum ) & 0xFF;
	packet[len-2] = checksum;
	packet[len-1] = '\n';

	//send via uart
	HAL_UART_Transmit(huart_com, packet, len, 10);
}

void COM_sendACK()
{
	uint8_t packet[] = { COM_ACK };
	COM_sendPacket(packet, 1);
}

void COM_sendDone()
{
	uint8_t packet[] = { COM_DONE };
	COM_sendPacket(packet, 1);
}

void COM_sendInfo(float x, float y, float z, float q1, float q2, float q3, uint8_t magnet)
{
	const uint8_t len = 1+4*6+1;
	float input_arr[6] = { x, y, z, q1, q2, q3};
	floatArray pool;

	uint8_t packet[len];

	packet[0] = COM_INFO;

	for(uint8_t i = 0; i < 6; i++)
	{
		pool.var = input_arr[i];
		memcpy(packet+1 + i*4, pool.bytes, 4);
	}
	packet[len-1] = magnet;
	COM_sendPacket(packet, len);
}

int _write(int file, unsigned char *ptr, int len)
{
	uint8_t packet[len+1];
	packet[0] = COM_MSG;
	memcpy(packet+1, ptr, len);
	COM_sendPacket(packet, len+1);
	return len;
}




