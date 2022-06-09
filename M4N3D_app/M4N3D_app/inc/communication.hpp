#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <cstdint>

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

#endif // COMMUNICATION_HPP
