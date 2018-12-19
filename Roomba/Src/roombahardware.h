#pragma once

#include "room.h"
#include "sensor.h"
#include <cstddef>
#include <unordered_map>

class Room;

class RoombaHardware
{
  public:
    RoombaHardware(size_t battery) : m_battery(battery), m_cleanState(false){};

    RoombaHardware(const RoombaHardware& other) = delete;

    bool move(Room& room);

    void rotate(Room& room, const Direction& dir);

    void setCleanMode(bool cleanState);

    bool getCleanMode() const;

    void setBattery(const size_t battery);

    void addSensor(const Direction& dir);

    void removeSensor(const Direction& dir);

    Sensor& getSensor(const Direction& dir);

  private:
    void updateBattery();

    size_t m_battery;
    bool m_cleanState;
    std::unordered_map<Direction, Sensor> m_sensors;
};
