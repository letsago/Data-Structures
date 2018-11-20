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
    m_roomba.setCleanMode(true);

    if(!m_roomProperties.isRoomExplored)
    {
        std::stack<Coordinate> spaces;
        explore(spaces, room);

        while(!spaces.empty())
        {
            Coordinate pos = spaces.top();
            spaces.pop();
            moveTo(pos, room);
            explore(spaces, room);
        }

        m_roomProperties.isRoomExplored = true;
    }
    else if(m_roomba.getCleanMode())
    {
        while(!m_roomProperties.dirtySpaces.empty())
        {
            Coordinate coor = m_roomProperties.dirtySpaces.top();
            m_roomProperties.dirtySpaces.pop();
            moveTo(coor, room);
        }
    }
}

void RoombaBrain::explore(std::stack<Coordinate>& stack, Room& room)
{
    for(size_t i = 0; i < Direction::COUNT; ++i)
    {
        Coordinate oldCoor = m_roombaProperties.coor;
        Coordinate newCoor = oldCoor + Coordinate::GetCoordinateFromDirection(m_roombaProperties.dir);

        if(!m_graph.contains(newCoor))
        {
            move(room);

            if(oldCoor != m_roombaProperties.coor)
            {
                stack.push(m_roombaProperties.coor);
                m_graph.connect(oldCoor, m_roombaProperties.coor, 1);

                if(!m_roomba.getCleanMode())
                    m_roomProperties.dirtySpaces.push(m_roombaProperties.coor);

                // rotate twice to face dir of original coor, move to original coor, then rotate twice again to face
                // original dir so that all directions will be explored
                rotate(room);
                rotate(room);
                move(room);
                rotate(room);
                rotate(room);
            }
        }

        rotate(room);
    }
}

void RoombaBrain::moveTo(const Coordinate& pos, Room& room)
{
    std::queue<Coordinate> path;
    m_graph.shortestDistance(m_roombaProperties.coor, pos, &path);

    while(!path.empty())
    {
        Coordinate next = path.front();
        path.pop();
        Direction nextDir = Coordinate::GetDirectionFromUnitCoordinate(next - m_roombaProperties.coor);

        while(m_roombaProperties.dir != nextDir)
            rotate(room);

        move(room);
    }
}
