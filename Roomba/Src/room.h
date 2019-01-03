#pragma once

#include "globals.h"
#include "roombahardware.h"
#include <fstream>
#include <iostream>
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

    void updateSensor(Sensor& sensor, const Direction& dir) const;

  private:
    void rotate(RoombaHardware& roomba, const Direction& dir);

    void move(RoombaHardware& roomba);

    void clear();

    const RoomSpace& getRoom(const Coordinate& coor) const;

    RoomSpace& getRoom(const Coordinate& coor);

    void throwIfCoorInvalid(const Coordinate& coor) const;

    std::vector<std::vector<RoomSpace>> m_room;
    RoombaProperties m_roombaProperties;
    size_t m_dirtySpaces;

    friend class RoombaHardware;
};
