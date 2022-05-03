#include "servo.h"


void _SRV_sendPacket(uint8_t *packet, uint8_t len )
{
	HAL_HalfDuplex_EnableTransmitter(&huart1);
	HAL_UART_Transmit(&huart1, packet , len, 50);
	HAL_HalfDuplex_EnableReceiver(&huart1);
}

void SRV_setLED(uint8_t id, uint8_t state)
{
	const uint8_t len = 8;
	uint8_t packet[len];

	uint8_t Checksum = (~(id + AX_LED_LENGTH + AX_WRITE_DATA + AX_LED + state)) & 0xFF;

	packet[0] = AX_START;
	packet[1] = AX_START;
	packet[2] = id;
	packet[3] = AX_LED_LENGTH;
	packet[4] = AX_WRITE_DATA;
	packet[5] = AX_LED;
	packet[6] = state;
	packet[7] = Checksum;

	_SRV_sendPacket(packet, len);
}


void SRV_changeID(uint8_t id, uint8_t new_id )
{
	const uint8_t len = 8;
	uint8_t packet[len];

	uint8_t Checksum = (~(id + AX_LED_LENGTH + AX_WRITE_DATA + AX_ID + new_id)) & 0xFF;

	packet[0] = AX_START;
	packet[1] = AX_START;
	packet[2] = id;
	packet[3] = AX_ID_LENGTH;
	packet[4] = AX_WRITE_DATA;
	packet[5] = AX_ID;
	packet[6] = new_id;
	packet[7] = Checksum;

	_SRV_sendPacket(packet, len);
}


void SRV_move(uint8_t id, int position, int speed)
{
    uint8_t Position_H,Position_L,Speed_H,Speed_L;
    Position_H = position >> 8;           // 16 bits - 2 x 8 bits variables
    Position_L = position;
    Speed_H = speed >> 8;
    Speed_L = speed;                      // 16 bits - 2 x 8 bits variables


    const uint8_t length = 11;
    uint8_t packet[length];

	uint8_t Checksum = (~(id + AX_GOAL_SP_LENGTH + AX_WRITE_DATA + AX_GOAL_POSITION_L + Position_L + Position_H + Speed_L + Speed_H)) & 0xFF;

    packet[0] = AX_START;
    packet[1] = AX_START;
    packet[2] = id;
    packet[3] = AX_GOAL_SP_LENGTH;
    packet[4] = AX_WRITE_DATA;
    packet[5] = AX_GOAL_POSITION_L;
    packet[6] = Position_L;
    packet[7] = Position_H;
    packet[8] = Speed_L;
    packet[9] = Speed_H;
    packet[10] = Checksum;

    _SRV_sendPacket(packet, length);
}


