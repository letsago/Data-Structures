#pragma once

#include "room.h"
#include <cstddef>

class Room;

class RoombaHardware
{
  public:
    RoombaHardware(size_t battery) : m_battery(battery){};

    RoombaHardware(const RoombaHardware& other) = delete;

    bool move(Room& room)
    {
        if(m_battery == 0)
            throw "battery is depleted";
        else
            --m_battery;

        return false;
    }

    void rotate()
    {
        if(m_battery == 0)
            throw "battery is depleted";
        else
            --m_battery;
    }

    void setCleanMode()
    {
        if(m_battery == 0)
            throw "battery is depleted";
        else
            --m_battery;
    }

    void setBattery(size_t battery) { m_battery = battery; }

    size_t getBattery() { return m_battery; }

  private:
    size_t m_battery;
};
