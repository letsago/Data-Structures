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

void RoombaHardware::rotate(Room& room)
{
    if(m_battery == 0)
    {
        throw std::out_of_range("battery is depleted");
    }
    --m_battery;

    room.rotate(*this);
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

void RoombaHardware::setBattery(size_t battery) { m_battery = battery; }
