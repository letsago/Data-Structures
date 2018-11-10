#pragma once

#include "room.h"
#include <cstddef>

class Room;

class RoombaHardware
{
  public:
    RoombaHardware(size_t battery) : m_battery(battery), m_cleanState(false){};

    RoombaHardware(const RoombaHardware& other) = delete;

    bool move(Room& room);

    void rotate(Room& room);

    void setCleanMode(bool cleanState);

    void setBattery(size_t battery);

  private:
    size_t m_battery;
    bool m_cleanState;
};
