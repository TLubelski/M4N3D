#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <QByteArray>
#include <cstdint>
#include "communication.hpp"

class CmdInterface
{
private:
  int index;
public:
  CmdInterface(int _index) : index(_index) {}
  int getIndex(){return index;};
  virtual QByteArray getPacket() = 0;
};


class CmdStart : public CmdInterface
{
public:
  CmdStart(int index) : CmdInterface(index) {}
  QByteArray getPacket() override
  {
    QByteArray packet;
    packet.append(LEN_START);
    packet.append(START);
    return packet;
  }
};

class CmdStop : public CmdInterface
{
public:
  CmdStop(int index) : CmdInterface(index) {}
  QByteArray getPacket() override
  {
    QByteArray packet;
    packet.append(LEN_STOP);
    packet.append(STOP);
    return packet;
  }
};

class CmdMagnet : public CmdInterface
{
private:
  bool state;
public:
  CmdMagnet(int index, bool _state ) : CmdInterface(index), state(_state) {}
  QByteArray getPacket() override
  {
    QByteArray packet;
    packet.append(LEN_MAGNET);
    packet.append(MAGNET);
    packet.append(state);
    return packet;
  }
};

class CmdWait : public CmdInterface
{
private:
  uint32_t duration;
public:
  CmdWait(int index, uint32_t _duration ) : CmdInterface(index), duration(_duration) {}
  QByteArray getPacket() override
  {
    QByteArray packet;
    packet.append(LEN_WAIT);
    packet.append(WAIT);
    u32Array pool = {duration};
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    return packet;
  }
};

class CmdMoveJ : public CmdInterface
{
private:
  float x, y, z;
public:
  CmdMoveJ(int index, float _x, float _y, float _z ) : CmdInterface(index), x(_x), y(_y), z(_z) {}
  QByteArray getPacket() override
  {
    QByteArray packet;
    packet.append(LEN_MOVEJ);
    packet.append(MOVEJ);
    floatArray pool = {x};
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    pool.var = y;
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    pool.var = z;
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    return packet;
  }
};

class CmdMoveL : public CmdInterface
{
private:
  float x, y, z;
public:
  CmdMoveL(int index, float _x, float _y, float _z ) : CmdInterface(index), x(_x), y(_y), z(_z) {}
  QByteArray getPacket() override
  {
    QByteArray packet;
    packet.append(LEN_MOVEL);
    packet.append(MOVEL);
    floatArray pool = {x};
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    pool.var = y;
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    pool.var = z;
    for(int i = 0; i < 4; i++ )
      packet.append(pool.bytes[i]);
    return packet;
  }
};


#endif // COMMAND_HPP
