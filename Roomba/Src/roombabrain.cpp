#include "roombabrain.h"

bool RoombaBrain::isClean() const { return m_roomProperties.isRoomExplored && m_roomProperties.dirtySpaces.empty(); }

std::ostream& operator<<(std::ostream& os, RoombaBrain& roombaBrain)
{
    Coordinate coor = {0, 0};

    for(size_t row = 0; row < roombaBrain.m_room.size(); ++row)
    {
        coor.x = row;

        for(size_t col = 0; col < roombaBrain.m_room[row].size(); ++col)
        {
            coor.y = col;
            os << roombaBrain.getRoom(coor).getColor();

            if(coor == roombaBrain.m_roombaProperties.coor - roombaBrain.m_gridDimensions.min)
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
    m_roombaProperties.dir = static_cast<Direction>((m_roombaProperties.dir + 1) % Direction::COUNT);
}

void RoombaBrain::step(Room& room)
{
    if(!m_resetCommands.empty())
    {
        Command command = m_resetCommands.front();
        m_resetCommands.pop();

        switch(command)
        {
        case MOVE:
            move(room);
            break;
        case ROTATE:
            rotate(room, RIGHT);
            break;
        default:
            break;
        }
    }
    else if(!m_mainCommands.empty())
    {
        Command command = m_mainCommands.front();
        m_mainCommands.pop();

        switch(command)
        {
        case MOVE:
            move(room);
            break;
        case ROTATE:
            rotate(room, RIGHT);
            break;
        case SETCLEANMODE:
            m_roomba.setCleanMode(true);
            getRoom(m_roombaProperties.coor).isClean = true;
            break;
        case EXPLORE:
        {
            Coordinate oldCoor = m_roombaProperties.coor;
            Coordinate newCoor = oldCoor + Coordinate::GetCoordinateFromDirection(m_roombaProperties.dir);

            if(newCoor > m_gridDimensions.max || newCoor < m_gridDimensions.min)
            {
                updatePrintBuffer(oldCoor, newCoor);
                m_gridDimensions.max.x = std::max(m_gridDimensions.max.x, newCoor.x);
                m_gridDimensions.max.y = std::max(m_gridDimensions.max.y, newCoor.y);
                m_gridDimensions.min.x = std::min(m_gridDimensions.min.x, newCoor.x);
                m_gridDimensions.min.y = std::min(m_gridDimensions.min.y, newCoor.y);
            }

            getRoom(newCoor - m_gridDimensions.min).isKnown = true;
            move(room);

            if(oldCoor != m_roombaProperties.coor)
            {
                m_spaces.push(m_roombaProperties.coor);
                m_graph.connect(oldCoor, m_roombaProperties.coor, 1);
                getRoom(m_roombaProperties.coor - m_gridDimensions.min).isTraversable = true;

                if(!m_roomba.getCleanMode())
                {
                    m_roomProperties.dirtySpaces.push(m_roombaProperties.coor);
                }
                else
                {
                    getRoom(m_roombaProperties.coor - m_gridDimensions.min).isClean = true;
                }

                // rotate twice to face dir of original coor, move to original coor, then rotate twice again to
                // face original dir so that all directions will be explored
                m_resetCommands.push(ROTATE);
                m_resetCommands.push(ROTATE);
                m_resetCommands.push(MOVE);
                m_resetCommands.push(ROTATE);
                m_resetCommands.push(ROTATE);
            }
            else
            {
                getRoom(newCoor - m_gridDimensions.min).isTraversable = false;
            }

            m_mainCommands.push(ROTATE);
            break;
        }
        }
    }
    else if(!isClean())
    {
        if(!m_roomProperties.isRoomExplored)
        {
            if(!m_spaces.empty())
            {
                if(m_counter % 2 == 0)
                {
                    explore();
                }
                else
                {
                    Coordinate pos = m_spaces.top();
                    m_spaces.pop();
                    moveTo(pos);
                }

                ++m_counter;
            }
            else
            {
                m_roomProperties.isRoomExplored = true;
            }
        }
        else if(m_roomba.getCleanMode())
        {
            if(!m_roomProperties.dirtySpaces.empty())
            {
                Coordinate coor = m_roomProperties.dirtySpaces.top();
                m_roomProperties.dirtySpaces.pop();
                moveTo(coor);
            }
        }
    }
}

void RoombaBrain::explore()
{
    Direction curr = m_roombaProperties.dir;

    for(size_t i = 0; i < Direction::COUNT; ++i)
    {
        Coordinate newCoor = m_roombaProperties.coor + Coordinate::GetCoordinateFromDirection(curr);

        if(!m_graph.contains(newCoor))
        {
            m_mainCommands.push(EXPLORE);
        }

        m_mainCommands.push(ROTATE);
        curr = static_cast<Direction>((curr + 1) % Direction::COUNT);
    }
}

void RoombaBrain::moveTo(const Coordinate& pos)
{
    std::queue<Coordinate> path;
    m_graph.shortestDistance(m_roombaProperties.coor, pos, &path);
    Coordinate curr = m_roombaProperties.coor;
    Direction currDir = m_roombaProperties.dir;

    while(!path.empty())
    {
        Coordinate next = path.front();
        path.pop();
        Direction nextDir = Coordinate::GetDirectionFromUnitCoordinate(next - curr);
        int rotNum = nextDir - currDir;

        if(rotNum < 0)
        {
            rotNum += Direction::COUNT;
        }

        for(size_t i = 0; i < rotNum; ++i)
        {
            m_mainCommands.push(ROTATE);
        }

        m_mainCommands.push(MOVE);
        curr = next;
        currDir = nextDir;
    }
}

const RoomSpace& RoombaBrain::getRoom(const Coordinate& coor) const { return m_room[coor.x][coor.y]; }

RoomSpace& RoombaBrain::getRoom(const Coordinate& coor) { return m_room[coor.x][coor.y]; }

void RoombaBrain::updatePrintBuffer(const Coordinate& oldDimensions, const Coordinate& newDimensions)
{
    RoomSpace space({false, false, false});

    if(oldDimensions.x != newDimensions.x)
    {
        std::vector<RoomSpace> newRow(m_room[0].size(), space);

        if(newDimensions.x > oldDimensions.x)
        {
            m_room.push_back(newRow);
        }
        else
        {
            m_room.insert(m_room.begin(), newRow);
        }
    }
    else if(oldDimensions.y != newDimensions.y)
    {
        if(newDimensions.y > oldDimensions.y)
        {
            for(size_t i = 0; i < m_room.size(); ++i)
            {
                m_room[i].push_back(space);
            }
        }
        else
        {
            for(size_t i = 0; i < m_room.size(); ++i)
            {
                m_room[i].insert(m_room[i].begin(), space);
            }
        }
    }
}
