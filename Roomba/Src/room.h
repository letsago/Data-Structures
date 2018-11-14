#pragma once

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

    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        COUNT
    };

    struct Coordinate
    {
        size_t x;
        size_t y;

        bool operator==(const Coordinate& other) { return (x == other.x && y == other.y); }
    };

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
    };

    struct RoomSpace
    {
        bool isTraversable;
        bool isClean;
    };

    const RoomSpace& getRoom(Coordinate coor) const;

    RoomSpace& getRoom(Coordinate coor);

    std::vector<std::vector<RoomSpace>> m_room;
    RoombaProperties m_roombaProperties;
    size_t m_dirtySpaces;

    friend class RoombaHardware;
};
