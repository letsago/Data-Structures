#include "roombabrain.h"

bool RoombaBrain::isClean() const { return m_roomProperties.isRoomExplored && m_roomProperties.dirtySpaces.empty(); }

void RoombaBrain::move(Room& room)
{
    if(m_roomba.move(room))
    {
        m_roombaProperties.coor += Coordinate::GetCoordinateFromDirection(m_roombaProperties.dir);
    }
}

void RoombaBrain::rotate(Room& room)
{
    m_roomba.rotate(room);
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
            rotate(room);
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
            rotate(room);
            break;
        case SETCLEANMODE:
            m_roomba.setCleanMode(true);
            break;
        case EXPLORE:
        {
            Coordinate oldCoor = m_roombaProperties.coor;
            move(room);

            if(oldCoor != m_roombaProperties.coor)
            {
                m_spaces.push(m_roombaProperties.coor);
                m_graph.connect(oldCoor, m_roombaProperties.coor, 1);

                if(!m_roomba.getCleanMode())
                {
                    m_roomProperties.dirtySpaces.push(m_roombaProperties.coor);
                }

                // rotate twice to face dir of original coor, move to original coor, then rotate twice again to
                // face original dir so that all directions will be explored
                m_resetCommands.push(ROTATE);
                m_resetCommands.push(ROTATE);
                m_resetCommands.push(MOVE);
                m_resetCommands.push(ROTATE);
                m_resetCommands.push(ROTATE);
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
