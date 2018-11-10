#include "room.h"

Room::Room(std::string file) : m_roomDimensions({0, 0})
{
    std::ifstream inf(file);

    if(!inf)
    {
        std::cerr << "Uh oh, could not be opened for reading!" << std::endl;
        exit(1);
    }

    inf >> *this;
}

bool Room::isClean() const { return false; }

void Room::dropRoomba(size_t x, size_t y, Direction dir, RoombaHardware& roomba)
{
    if(m_room.at(x * m_roomDimensions.columnCount + y) == ' ')
        m_room.replace(x * m_roomDimensions.columnCount + y, 1, "x");
    else
        throw std::out_of_range("cannot drop roomba here");

    m_roombaProperties.roombaCoor1 = x;
    m_roombaProperties.roombaCoor2 = y;
    m_roombaProperties.roombaDir = dir;
}

void Room::rotate(RoombaHardware& roomba)
{
    m_roombaProperties.roombaDir = static_cast<Direction>((m_roombaProperties.roombaDir + 1) % Room::Direction::COUNT);
}

void Room::move(RoombaHardware& roomba)
{
    size_t roombaCoor1 = m_roombaProperties.roombaCoor1;
    size_t roombaCoor2 = m_roombaProperties.roombaCoor2;

    switch(m_roombaProperties.roombaDir)
    {
    case UP:
        --roombaCoor1;
        break;
    case RIGHT:
        ++roombaCoor2;
        break;
    case DOWN:
        ++roombaCoor1;
        break;
    case LEFT:
        --roombaCoor2;
        break;
    default:
        break;
    }

    if(m_room.at(roombaCoor1 * m_roomDimensions.columnCount + roombaCoor2) != '#')
    {
        m_room.replace(m_roombaProperties.roombaCoor1 * m_roomDimensions.columnCount + m_roombaProperties.roombaCoor2,
                       1, " ");
        m_room.replace(roombaCoor1 * m_roomDimensions.columnCount + roombaCoor2, 1, "x");
        m_roombaProperties.roombaCoor1 = roombaCoor1;
        m_roombaProperties.roombaCoor2 = roombaCoor2;
    }
    else
        throw std::out_of_range("roomba didn't move");
}

void Room::clear()
{
    m_room.clear();
    m_roomDimensions.rowCount = 0;
    m_roomDimensions.columnCount = 0;
}
