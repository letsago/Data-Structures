#include "room.h"

Room::Room(const std::string& file) : m_dirtySpaces(0)
{
    std::ifstream inf(file);

    if(!inf)
    {
        std::cerr << "Uh oh, could not be opened for reading!" << std::endl;
        exit(1);
    }

    inf >> *this;
}

std::ostream& operator<<(std::ostream& os, const Room& room)
{
    Coordinate coor = {0, 0};

    for(size_t row = 0; row < room.m_room.size(); ++row)
    {
        coor.x = row;

        for(size_t col = 0; col < room.m_room[row].size(); ++col)
        {
            coor.y = col;
            os << room.getRoom(coor).getColor();

            if(coor == room.m_roombaProperties.coor)
            {
                os << room.m_roombaProperties;
            }
            else
            {
                os << room.getRoom(coor).getSymbol();
            }
        }

        os << std::endl;
    }

    os << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Room& room)
{
    room.clear();
    std::vector<RoomSpace> rowRoom;

    while(is)
    {
        std::string strInput;
        getline(is, strInput);

        if(!strInput.empty())
        {
            rowRoom.resize(strInput.length());

            for(size_t i = 0; i < strInput.length(); ++i)
            {
                RoomSpace space;
                space.isClean = false;
                space.isKnown = true;

                if(strInput[i] == ' ')
                {
                    ++room.m_dirtySpaces;
                    space.isTraversable = true;
                }
                else
                {
                    space.isTraversable = false;
                }

                rowRoom[i] = space;
            }

            room.m_room.push_back(rowRoom);
        }
    }

    return is;
}

bool Room::isClean() const { return m_dirtySpaces == 0; }

void Room::dropRoomba(const Coordinate& coor, const Direction& dir, const RoombaHardware& roomba)
{
    if(!getRoom(coor).isTraversable)
    {
        throw std::out_of_range("cannot drop roomba here");
    }
    if(roomba.getCleanMode())
    {
        getRoom(coor).isClean = true;
        --m_dirtySpaces;
    }

    m_roombaProperties.coor = coor;
    m_roombaProperties.dir = dir;
}

void Room::rotate(RoombaHardware& roomba, const Direction& dir)
{
    if(dir == Direction::RIGHT)
    {
        m_roombaProperties.dir = static_cast<Direction>((m_roombaProperties.dir + 1) % Direction::COUNT);
    }
    else if(dir == Direction::LEFT)
    {
        m_roombaProperties.dir = static_cast<Direction>((m_roombaProperties.dir + 3) % Direction::COUNT);
    }
    else
    {
        throw std::out_of_range("invalid direction to rotate roomba");
    }
}

void Room::move(RoombaHardware& roomba)
{
    Coordinate roombaNewCoor = m_roombaProperties.coor;

    if(roomba.getCleanMode() && !getRoom(roombaNewCoor).isClean)
    {
        --m_dirtySpaces;
        getRoom(roombaNewCoor).isClean = true;
    }

    roombaNewCoor += Coordinate::GetCoordinateFromDirection(m_roombaProperties.dir);

    if(!getRoom(roombaNewCoor).isTraversable)
    {
        throw std::out_of_range("roomba didn't move");
    }
    if(roomba.getCleanMode() && !getRoom(roombaNewCoor).isClean)
    {
        --m_dirtySpaces;
        getRoom(roombaNewCoor).isClean = true;
    }

    m_roombaProperties.coor = roombaNewCoor;
}

void Room::clear()
{
    m_room.clear();
    m_dirtySpaces = 0;
}

const RoomSpace& Room::getRoom(const Coordinate& coor) const
{
    throwIfCoorInvalid(coor);
    return m_room[coor.x][coor.y];
}

RoomSpace& Room::getRoom(const Coordinate& coor)
{
    throwIfCoorInvalid(coor);
    return m_room[coor.x][coor.y];
}

void Room::updateSensor(Sensor& sensor, const Direction& dir) const
{
    Coordinate absNeighbor = m_roombaProperties.coor + Coordinate::GetCoordinateFromDirection(static_cast<Direction>(
                                                           (m_roombaProperties.dir + dir) % Direction::COUNT));
    sensor.sensorSet(getRoom(absNeighbor).isTraversable);
}

void Room::throwIfCoorInvalid(const Coordinate& coor) const
{
    if(m_room.empty() || m_room[coor.x].empty() || coor.x > m_room.size() - 1 || coor.x < 0 ||
       coor.y > m_room[coor.x].size() - 1 || coor.y < 0)
    {
        throw std::out_of_range("cannot get room from invalid coordinate");
    };
}
