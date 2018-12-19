#include "roombabrain.h"
#include <assert.h>

bool RoombaBrain::isClean() const { return m_roomProperties.isRoomExplored && m_roomProperties.dirtySpaces.empty(); }

std::ostream& operator<<(std::ostream& os, RoombaBrain& roombaBrain)
{
    Coordinate coor = {0, 0};

    for(size_t row = 0; row < roombaBrain.m_roomProperties.room.size(); ++row)
    {
        coor.x = row;

        for(size_t col = 0; col < roombaBrain.m_roomProperties.room[row].size(); ++col)
        {
            coor.y = col;
            os << roombaBrain.getRoom(coor).getColor();

            if(coor == roombaBrain.m_roombaProperties.coor - roombaBrain.m_roomProperties.gridDimensions.min)
            {
                if(roombaBrain.getRoom(coor).isClean)
                {
                    os << roombaBrain.m_roombaProperties;
                }
            }
            else
            {
                os << roombaBrain.getRoom(coor).getSymbol();
            }
        }

        os << RESET;
        os << std::endl;
    }

    os << std::endl;
    return os;
}

void RoombaBrain::move(Room& room)
{
    if(m_roomba.move(room))
    {
        m_roombaProperties.coor += Coordinate::GetCoordinateFromDirection(m_roombaProperties.dir);
    }
}

void RoombaBrain::rotate(Room& room, const Direction& dir)
{
    m_roomba.rotate(room, dir);

    if(dir == Direction::RIGHT)
    {
        m_roombaProperties.dir = static_cast<Direction>((m_roombaProperties.dir + 1) % Direction::COUNT);
    }
    else if(dir == Direction::LEFT)
    {
        m_roombaProperties.dir = static_cast<Direction>((m_roombaProperties.dir + 3) % Direction::COUNT);
    }
}

void RoombaBrain::step(Room& room)
{
    updateRoom();

    if(!m_mainCommands.empty())
    {
        Command command = m_mainCommands.front();
        m_mainCommands.pop();

        switch(command)
        {
        case MOVE:
            move(room);
            if(m_roomba.getCleanMode())
            {
                getRoom(m_roombaProperties.coor).isClean = true;
            }
            break;
        case ROTATERIGHT:
            rotate(room, RIGHT);
            break;
        case ROTATELEFT:
            rotate(room, LEFT);
            break;
        case SETCLEANMODE:
            m_roomba.setCleanMode(true);
            getRoom(m_roombaProperties.coor) = {true, true, true};
            break;
        }
    }
    else if(!isClean())
    {
        if(m_roomba.getCleanMode() && !m_roomProperties.dirtySpaces.empty())
        {
            Coordinate coor = findClosestCoor(m_roomProperties.dirtySpaces);
            m_roomProperties.dirtySpaces.erase(coor);
            m_roomProperties.nonTraversedSpaces.erase(coor);
            moveTo(coor);
        }
        else if(!m_roomProperties.isRoomExplored)
        {
            if(!m_roomProperties.nonTraversedSpaces.empty())
            {
                Coordinate pos = findClosestCoor(m_roomProperties.nonTraversedSpaces);
                m_roomProperties.nonTraversedSpaces.erase(pos);
                moveTo(pos);
            }
            else
            {
                m_roomProperties.isRoomExplored = true;
            }
        }
    }
}

void RoombaBrain::moveTo(const Coordinate& pos)
{
    std::queue<Coordinate> path;
    size_t minDis = m_graph.shortestDistance(m_roombaProperties.coor, pos, &path);
    Coordinate curr = m_roombaProperties.coor;
    Direction currDir = m_roombaProperties.dir;
    assert(minDis == path.size());

    while(!path.empty())
    {
        Coordinate next = path.front();
        path.pop();
        Direction nextDir = Coordinate::GetDirectionFromUnitCoordinate(next - curr);
        int rotNum = (nextDir - currDir + Direction::COUNT) % Direction::COUNT;

        if(rotNum == 3)
        {
            m_mainCommands.push(ROTATELEFT);
        }
        else
        {
            for(size_t i = 0; i < rotNum; ++i)
            {
                m_mainCommands.push(ROTATERIGHT);
            }
        }

        m_mainCommands.push(MOVE);
        curr = next;
        currDir = nextDir;
    }
}

const RoomSpace& RoombaBrain::getRoom(const Coordinate& coor) const { return m_roomProperties.room[coor.x][coor.y]; }

RoomSpace& RoombaBrain::getRoom(const Coordinate& coor) { return m_roomProperties.room[coor.x][coor.y]; }

void RoombaBrain::updatePrintBuffer(const Coordinate& oldDimensions, const Coordinate& newDimensions)
{
    RoomSpace space({false, false, false});

    if(oldDimensions.x != newDimensions.x)
    {
        std::vector<RoomSpace> newRow(m_roomProperties.room[0].size(), space);

        if(newDimensions.x > oldDimensions.x)
        {
            m_roomProperties.room.push_back(newRow);
        }
        else
        {
            m_roomProperties.room.insert(m_roomProperties.room.begin(), newRow);
        }
    }
    else if(oldDimensions.y != newDimensions.y)
    {
        if(newDimensions.y > oldDimensions.y)
        {
            for(size_t i = 0; i < m_roomProperties.room.size(); ++i)
            {
                m_roomProperties.room[i].push_back(space);
            }
        }
        else
        {
            for(size_t i = 0; i < m_roomProperties.room.size(); ++i)
            {
                m_roomProperties.room[i].insert(m_roomProperties.room[i].begin(), space);
            }
        }
    }
}

Coordinate RoombaBrain::findClosestCoor(const std::unordered_set<Coordinate, CoordinateHash>& set) const
{
    if(set.empty())
    {
        throw std::out_of_range("no coordinates to find from");
    }

    Coordinate target = *set.begin();
    size_t minDis = m_graph.shortestDistance(m_roombaProperties.coor, target);

    for(auto it = set.begin(); it != set.end(); ++it)
    {
        if(m_graph.shortestDistance(m_roombaProperties.coor, *it) < minDis)
        {
            minDis = m_graph.shortestDistance(m_roombaProperties.coor, *it);
            target = *it;
        }
    }

    return target;
}

void RoombaBrain::updateRoom()
{
    for(size_t i = 0; i < Direction::COUNT; ++i)
    {
        Coordinate relNeighbor =
            m_roombaProperties.coor + Coordinate::GetCoordinateFromDirection(
                                          static_cast<Direction>((m_roombaProperties.dir + i) % Direction::COUNT));

        if(relNeighbor > m_roomProperties.gridDimensions.max || relNeighbor < m_roomProperties.gridDimensions.min)
        {
            updatePrintBuffer(m_roombaProperties.coor, relNeighbor);
            m_roomProperties.gridDimensions.max.x = std::max(m_roomProperties.gridDimensions.max.x, relNeighbor.x);
            m_roomProperties.gridDimensions.max.y = std::max(m_roomProperties.gridDimensions.max.y, relNeighbor.y);
            m_roomProperties.gridDimensions.min.x = std::min(m_roomProperties.gridDimensions.min.x, relNeighbor.x);
            m_roomProperties.gridDimensions.min.y = std::min(m_roomProperties.gridDimensions.min.y, relNeighbor.y);
        }

        getRoom(relNeighbor - m_roomProperties.gridDimensions.min).isKnown = true;

        if(m_roomba.getSensor(static_cast<Direction>(i)).sensorRead())
        {
            if(!m_graph.contains(relNeighbor))
            {
                m_roomProperties.nonTraversedSpaces.insert(relNeighbor);
                m_roomProperties.dirtySpaces.insert(relNeighbor);
                getRoom(relNeighbor - m_roomProperties.gridDimensions.min).isTraversable = true;
            }

            m_graph.connect(m_roombaProperties.coor, relNeighbor, 1);
        }
    }
}
