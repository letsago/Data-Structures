#pragma once

#include "globals.h"
#include "graph.h"
#include "room.h"
#include <queue>
#include <stack>

class RoombaBrain
{
  public:
    RoombaBrain(RoombaHardware& roomba)
        : m_roomba(roomba), m_roombaProperties({{7, 7}, UP}), m_gridDimensions({{0, 0}, {15, 15}}), m_counter(0)
    {
        m_mainCommands.push(SETCLEANMODE);
        m_spaces.push(m_roombaProperties.coor);
        std::vector<RoomSpace> initRow(m_gridDimensions.max.y - m_gridDimensions.min.y + 1, {false, false, false});
        m_room.resize(m_gridDimensions.max.x - m_gridDimensions.min.x + 1, initRow);
    }

    RoombaBrain(const RoombaBrain& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, RoombaBrain& roombaBrain);

    bool isClean() const;

    void step(Room& room);

  private:
    struct RoomProperties
    {
        RoomProperties() : isRoomExplored(false){};

        bool isRoomExplored;
        std::stack<Coordinate> dirtySpaces;
    };

    struct GridDimensions
    {
        Coordinate min;
        Coordinate max;
    };

  private:
    // moves roomba one space in direction roomba is facing
    void move(Room& room);

    // rotates roomba 90 degrees to the right
    void rotate(Room& room);

    // moves to all previously nonvisited adjacent spaces to collect room info and moves back to original coor and dir
    void explore();

    // moves to designated position
    void moveTo(const Coordinate& pos);

    const RoomSpace& getRoom(const Coordinate& coor) const;

    RoomSpace& getRoom(const Coordinate& coor);

    void updatePrintBuffer(const Coordinate& oldDimensions, const Coordinate& newDimensions);

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
    GridDimensions m_gridDimensions;
    Graph<Coordinate, CoordinateHash> m_graph;
    std::vector<std::vector<RoomSpace>> m_room;
    std::queue<Command> m_mainCommands;
    std::queue<Command> m_resetCommands;
    std::stack<Coordinate> m_spaces;
    int m_counter;
};
