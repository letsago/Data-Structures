#pragma once

#include "roombahardware.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class Room
{
  public:
    Room() : m_roomDimensions({0, 0}){};

    Room(std::string file);

    Room(const Room& other) = delete;

    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        COUNT
    };

    friend std::ostream& operator<<(std::ostream& os, const Room& room)
    {
        os << room.m_room;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Room& room)
    {
        room.clear();

        while(is)
        {
            std::string strInput;
            getline(is, strInput);
            if(!strInput.empty())
            {
                strInput.append("\n");
                room.m_room.append(strInput);
                ++room.m_roomDimensions.rowCount;
            }
        }

        room.m_roomDimensions.columnCount = (room.m_room.length()) / room.m_roomDimensions.rowCount;
        room.m_room.append("\n");
        return is;
    }

    bool isClean() const;

    void dropRoomba(size_t x, size_t y, Direction dir, RoombaHardware& roomba);

  private:
    void rotate(RoombaHardware& roomba);

    void move(RoombaHardware& roomba);

    void clear();

    struct RoomDimensions
    {
        size_t rowCount;
        size_t columnCount;
    };

    struct RoombaProperties
    {
        size_t roombaCoor1;
        size_t roombaCoor2;
        Direction roombaDir;
    };

    std::string m_room;
    RoomDimensions m_roomDimensions;
    RoombaProperties m_roombaProperties;

    friend class RoombaHardware;
};
