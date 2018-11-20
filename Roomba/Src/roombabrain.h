#pragma once

#include "globals.h"
#include "graph.h"
#include "room.h"
#include <stack>

class RoombaBrain
{
  public:
    RoombaBrain(RoombaHardware& roomba) : m_roomba(roomba), m_roombaProperties({{0, 0}, RIGHT}) {}

    RoombaBrain(const RoombaBrain& other) = delete;

    bool isClean() const;

    void step(Room& room);

  private:
    struct RoombaProperties
    {
        Coordinate coor;
        Direction dir;
    };

    struct RoomProperties
    {
        RoomProperties() : isRoomExplored(false){};

        bool isRoomExplored;
        std::stack<Coordinate> dirtySpaces;
    };

    // moves roomba one space in direction roomba is facing
    void move(Room& room);

    // rotates roomba 90 degrees to the right
    void rotate(Room& room);

    // moves to all previously nonvisited adjacent spaces to collect room info and moves back to original coor and dir
    void explore(std::stack<Coordinate>& stack, Room& room);

    // moves to designated position
    void moveTo(const Coordinate& pos, Room& room);

    RoombaHardware& m_roomba;
    RoombaProperties m_roombaProperties;
    RoomProperties m_roomProperties;
    Graph<Coordinate, CoordinateHash> m_graph;
};
