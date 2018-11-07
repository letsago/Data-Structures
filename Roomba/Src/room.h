#pragma once

#include "roombahardware.h"
#include <string>

class Room
{
  public:
    Room(std::string file){};

    Room(const Room& other) = delete;

    bool isClean() { return false; }

    friend std::ostream& operator<<(std::ostream& os, const Room& room) { return os; }

    friend std::istream& operator>>(std::istream& is, Room& room) { return is; }

    void dropRoomba(size_t x, size_t y, size_t dir, RoombaHardware& roomba) {}

    void move(RoombaHardware& roomba) {}

    void rotate(RoombaHardware& roomba) {}
};
