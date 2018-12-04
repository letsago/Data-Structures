#pragma once

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

    Room(const std::string& file);

    Room(const Room& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Room& room);

    friend std::istream& operator>>(std::istream& is, Room& room);

    bool isClean() const;

    void dropRoomba(const Coordinate& coor, const Direction& dir, const RoombaHardware& roomba);

  private:
    void rotate(RoombaHardware& roomba);

    void move(RoombaHardware& roomba);

    void clear();

    const RoomSpace& getRoom(const Coordinate& coor) const;

    RoomSpace& getRoom(const Coordinate& coor);

    std::vector<std::vector<RoomSpace>> m_room;
    RoombaProperties m_roombaProperties;
    size_t m_dirtySpaces;

    friend class RoombaHardware;
};
