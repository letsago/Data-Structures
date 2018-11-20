#include "room.h"

Room::Room(std::string file) : m_dirtySpaces(0)
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

            if(coor == room.m_roombaProperties.roombaCoor)
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
    std::vector<Room::RoomSpace> rowRoom;

    while(is)
    {
        std::string strInput;
        getline(is, strInput);

        if(!strInput.empty())
        {
            rowRoom.resize(strInput.length());

            for(size_t i = 0; i < strInput.length(); ++i)
            {
                Room::RoomSpace space;
                space.isClean = false;

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

void Room::dropRoomba(Coordinate coor, Direction dir, RoombaHardware& roomba)
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

    m_roombaProperties.roombaCoor = coor;
    m_roombaProperties.roombaDir = dir;
}

void Room::rotate(RoombaHardware& roomba)
{
    m_roombaProperties.roombaDir = static_cast<Direction>((m_roombaProperties.roombaDir + 1) % Direction::COUNT);
}

void Room::move(RoombaHardware& roomba)
{
    Coordinate roombaNewCoor = m_roombaProperties.roombaCoor;

    if(roomba.getCleanMode() && !getRoom(roombaNewCoor).isClean)
    {
        --m_dirtySpaces;
        getRoom(roombaNewCoor).isClean = true;
    }

    roombaNewCoor += Coordinate::GetCoordinateFromDirection(m_roombaProperties.roombaDir);

    if(!getRoom(roombaNewCoor).isTraversable)
    {
        throw std::out_of_range("roomba didn't move");
    }
    if(roomba.getCleanMode() && !getRoom(roombaNewCoor).isClean)
    {
        --m_dirtySpaces;
        getRoom(roombaNewCoor).isClean = true;
    }

    m_roombaProperties.roombaCoor = roombaNewCoor;
}

void Room::clear()
{
    m_room.clear();
    m_dirtySpaces = 0;
}

const Room::RoomSpace& Room::getRoom(Coordinate coor) const { return m_room[coor.x][coor.y]; }

Room::RoomSpace& Room::getRoom(Coordinate coor) { return m_room[coor.x][coor.y]; }
