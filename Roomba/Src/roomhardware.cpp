#include "room.h"

bool RoombaHardware::move(Room& room)
{
    if(m_battery == 0)
    {
        throw std::out_of_range("battery is depleted");
    }
    --m_battery;

    try
    {
        room.move(*this);
        return true;
    }
    catch(std::out_of_range)
    {
        return false;
    }
}

void RoombaHardware::rotate(Room& room, const Direction& dir)
{
    if(m_battery == 0)
    {
        throw std::out_of_range("battery is depleted");
    }
    --m_battery;

    room.rotate(*this, dir);
}

void RoombaHardware::setCleanMode(bool cleanState)
{
    if(m_battery == 0)
    {
        throw std::out_of_range("battery is depleted");
    }
    --m_battery;

    m_cleanState = cleanState;
}

bool RoombaHardware::getCleanMode() const { return m_cleanState; }

void RoombaHardware::setBattery(const size_t battery) { m_battery = battery; }

void RoombaHardware::addSensor(const Direction& dir)
{
    if(m_sensors.find(dir) == m_sensors.end())
    {
        Sensor sensor;
        m_sensors.insert({dir, sensor});
    }
    else
    {
        throw std::out_of_range("cannot add sensor to roomba");
    }
}

void RoombaHardware::removeSensor(const Direction& dir)
{
    if(m_sensors.find(dir) != m_sensors.end())
    {
        m_sensors.erase(dir);
    }
    else
    {
        throw std::out_of_range("cannot find roomba sensor to remove");
    }
}

Sensor& RoombaHardware::getSensor(const Direction& dir)
{
    if(m_sensors.find(dir) != m_sensors.end())
    {
        --m_battery;
        return m_sensors.at(dir);
    }
    else
    {
        throw std::out_of_range("cannot find roomba sensor");
    }
}
