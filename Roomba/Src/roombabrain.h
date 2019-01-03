#pragma once

#include "graph.h"
#include "room.h"
#include <queue>
#include <unordered_set>

class RoombaBrain
{
  public:
    RoombaBrain(RoombaHardware& roomba)
        : m_roomba(roomba),
          m_roombaProperties({{7, 7}, DOWN}),
          m_roomProperties({m_roombaProperties.coor.x + 10, m_roombaProperties.coor.y + 10})
    {
        m_mainCommands.push(SETCLEANMODE);
    }

    RoombaBrain(const RoombaBrain& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, RoombaBrain& roombaBrain);

    bool isClean() const;

    void step(Room& room);

  private:
    struct GridDimensions
    {
        Coordinate min;
        Coordinate max;
    };

    struct RoomProperties
    {
        RoomProperties(const Coordinate& maxDim) : isRoomExplored(false), gridDimensions({{0, 0}, {maxDim.x, maxDim.y}})
        {
            std::vector<RoomSpace> initRow(gridDimensions.max.y - gridDimensions.min.y + 1, {false, false, false});
            room.resize(gridDimensions.max.x - gridDimensions.min.x + 1, initRow);
        };

        bool isRoomExplored;
        std::unordered_set<Coordinate, CoordinateHash> dirtySpaces;
        std::vector<std::vector<RoomSpace>> room;
        std::unordered_set<Coordinate, CoordinateHash> nonTraversedSpaces;
        GridDimensions gridDimensions;
    };

  private:
    // moves roomba one space in direction roomba is facing
    void move(Room& room);

    // rotates roomba 90 degrees to the right
    void rotate(Room& room, const Direction& dir);

    // moves to designated position
    void moveTo(const Coordinate& pos);

    const RoomSpace& getRoom(const Coordinate& coor) const;

    RoomSpace& getRoom(const Coordinate& coor);

    void updatePrintBuffer(const Coordinate& oldDimensions, const Coordinate& newDimensions);

    Coordinate findClosestCoor(const std::unordered_set<Coordinate, CoordinateHash>& set) const;

    void updateRoom();

    enum Command
    {
        MOVE,
        ROTATERIGHT,
        ROTATELEFT,
        SETCLEANMODE
    };

    RoombaHardware& m_roomba;
    RoombaProperties m_roombaProperties;
    RoomProperties m_roomProperties;
    Graph m_graph;
    std::queue<Command> m_mainCommands;
};
