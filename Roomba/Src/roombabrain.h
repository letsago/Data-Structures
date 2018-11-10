#pragma once

#include "room.h"

class RoombaBrain
{
  public:
    RoombaBrain(RoombaHardware& roomba) : m_roomba(roomba){};

    RoombaBrain(const RoombaBrain& other) = delete;

    bool isClean() const;

    void step(Room& room);

  private:
    RoombaHardware& m_roomba;
};
