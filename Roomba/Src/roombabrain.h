#pragma once

#include "roombahardware.h"

class RoombaBrain
{
  public:
    RoombaBrain(RoombaHardware& roomba) : m_roomba(roomba){};

    RoombaBrain(const RoombaBrain& other) = delete;

    bool isClean() { return false; }

    void step() { m_roomba.rotate(); }

  private:
    RoombaHardware& m_roomba;
};
