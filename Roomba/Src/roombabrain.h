#pragma once

#include "globals.h"
#include "graph.h"
#include "room.h"
#include <queue>
#include <stack>

class RoombaBrain
{
  public:
    RoombaBrain(RoombaHardware& roomba) : m_roomba(roomba), m_roombaProperties({{0, 0}, RIGHT}), m_counter(0)
    {
        m_mainCommands.push(SETCLEANMODE);
        m_spaces.push({0, 0});
    }

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
    void explore();

    // moves to designated position
    void moveTo(const Coordinate& pos);

    enum Command
    {
        MOVE,
        ROTATE,
        SETCLEANMODE,
        EXPLORE
    };

    RoombaHardware& m_roomba;
    RoombaProperties m_roombaProperties;
    RoomProperties m_roomProperties;
    Graph<Coordinate, CoordinateHash> m_graph;
    std::queue<Command> m_mainCommands;
    std::queue<Command> m_resetCommands;
    std::stack<Coordinate> m_spaces;
    int m_counter;
};
