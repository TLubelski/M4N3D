#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <cstdint>

#define LEN_START 1
#define LEN_STOP 1
#define LEN_MAGNET 2
#define LEN_MOVEJ 13
#define LEN_MOVEL 13
#define LEN_WAIT 5

typedef enum
{
    START = 1,
    STOP = 2,
    MOVEL = 3,
    MOVEJ = 4,
    WAIT = 5,
    MAGNET = 6,

    ACK = 11,
    DONE = 12,
    DATA = 13,
    DEBUG = 14
} MSG;

typedef union {
    float var;
    uint8_t bytes[4];
} floatArray;

typedef union {
    uint32_t var;
    uint8_t bytes[4];
} u32Array;

#define XY_LIMIT 80
#define Z_LIMIT 150



#endif // COMMUNICATION_HPP
