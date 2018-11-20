#pragma once

#include "colors.h"
#include "globals.h"
#include "roombahardware.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Room
{
  public:
    Room() : m_dirtySpaces(0){};

    Room(std::string file);

    Room(const Room& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Room& room);

    friend std::istream& operator>>(std::istream& is, Room& room);

    bool isClean() const;

    void dropRoomba(Coordinate coor, Direction dir, RoombaHardware& roomba);

  private:
    void rotate(RoombaHardware& roomba);

    void move(RoombaHardware& roomba);

    void clear();

    struct RoombaProperties
    {
        Coordinate roombaCoor;
        Direction roombaDir;

        friend std::ostream& operator<<(std::ostream& os, const RoombaProperties& roombaProperties)
        {
            switch(roombaProperties.roombaDir)
            {
            case UP:
                os << "^";
                break;
            case RIGHT:
                os << ">";
                break;
            case DOWN:
                os << "v";
                break;
            case LEFT:
                os << "<";
                break;
            default:
                break;
            }

            return os;
        }
    };

    struct RoomSpace
    {
        bool isTraversable;
        bool isClean;

        const std::string getColor() const
        {
            if(isClean)
                return BLUE;
            else
                return RESET;
        }

        const std::string getSymbol() const
        {
            if(isTraversable)
                return " ";
            else
                return "#";
        }

        friend std::ostream& operator<<(std::ostream& os, const RoomSpace& roomSpace)
        {
            if(!roomSpace.isTraversable)
                os << RESET << "#";
            else if(roomSpace.isClean)
                os << BLUE;
            else
                os << RESET;

            return os;
        }
    };

    const RoomSpace& getRoom(Coordinate coor) const;

    RoomSpace& getRoom(Coordinate coor);

    std::vector<std::vector<RoomSpace>> m_room;
    RoombaProperties m_roombaProperties;
    size_t m_dirtySpaces;

    friend class RoombaHardware;
};
