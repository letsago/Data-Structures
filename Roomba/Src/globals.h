#pragma once

#include "colors.h"
#include <iostream>

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    COUNT,
    NONE
};

inline size_t findRotationDiff(const Direction& self, const Direction& other)
{
    size_t rotationCost = (self - other + Direction::COUNT) % Direction::COUNT;

    if(rotationCost == 3)
    {
        rotationCost = 1;
    }

    return rotationCost;
}

struct Coordinate
{
    int x;
    int y;

    Coordinate operator+(const Coordinate& other) const
    {
        Coordinate result = {x, y};
        result.x += other.x;
        result.y += other.y;
        return result;
    }

    Coordinate& operator+=(const Coordinate& other)
    {
        *this = *this + other;
        return *this;
    }

    Coordinate operator-(const Coordinate& other) const
    {
        Coordinate result = {x, y};
        result.x -= other.x;
        result.y -= other.y;
        return result;
    }

    bool operator==(const Coordinate& other) const { return (x == other.x && y == other.y); }

    bool operator!=(const Coordinate& other) const { return !(x == other.x && y == other.y); }

    bool operator>(const Coordinate& other) const { return (x > other.x || y > other.y); }

    bool operator<(const Coordinate& other) const { return (x < other.x || y < other.y); }

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coor)
    {
        os << "(" << coor.x << ", " << coor.y << ")";
        return os;
    }

    static const Coordinate GetCoordinateFromDirection(const Direction& dir)
    {
        switch(dir)
        {
        case UP:
            return {-1, 0};
            break;
        case RIGHT:
            return {0, 1};
            break;
        case DOWN:
            return {1, 0};
            break;
        case LEFT:
            return {0, -1};
            break;
        default:
            throw std::out_of_range("cannot convert invalid direction to coordinate");
            break;
        }
    }

    static const Direction GetDirectionFromUnitCoordinate(const Coordinate& coor)
    {
        Direction dir;
        const Coordinate upCoor = {-1, 0};
        const Coordinate downCoor = {1, 0};
        const Coordinate rightCoor = {0, 1};
        const Coordinate leftCoor = {0, -1};

        if(coor == upCoor)
        {
            dir = UP;
        }
        else if(coor == downCoor)
        {
            dir = DOWN;
        }
        else if(coor == rightCoor)
        {
            dir = RIGHT;
        }
        else if(coor == leftCoor)
        {
            dir = LEFT;
        }
        else
        {
            throw std::out_of_range("can only find direction from a unit coordinate");
        }

        return dir;
    }

    static const std::pair<Direction, Direction> GetDirectionsfromVector(const Coordinate& vector)
    {
        std::pair<Direction, Direction> directions(Direction::NONE, Direction::NONE);

        if(vector.x > 0)
        {
            directions.first = Direction::DOWN;
        }
        else if(vector.x < 0)
        {
            directions.first = Direction::UP;
        }

        if(vector.y > 0)
        {
            directions.second = Direction::RIGHT;
        }
        else if(vector.y < 0)
        {
            directions.second = Direction::LEFT;
        }

        return directions;
    }
};

struct CoordinateHash
{
    size_t operator()(const Coordinate& coor) const
    {
        size_t h1 = std::hash<int>()(coor.x);
        size_t h2 = std::hash<int>()(coor.y);

        return h1 ^ (h2 << 1);
    }
};

struct RoombaProperties
{
    Coordinate coor;
    Direction dir;

    friend std::ostream& operator<<(std::ostream& os, const RoombaProperties& roombaProperties)
    {
        switch(roombaProperties.dir)
        {
        case UP:
            os << "^";
            break;
        case RIGHT:
            os << ">";
            break;
        case DOWN:
            os << "v";
            break;
        case LEFT:
            os << "<";
            break;
        default:
            break;
        }

        return os;
    }
};

struct RoomSpace
{
    bool isTraversable;
    bool isClean;
    bool isKnown;

    bool operator==(const RoomSpace& other) const
    {
        return isTraversable == other.isTraversable && isClean == other.isClean && isKnown == other.isKnown;
    }

    const std::string getColor() const
    {
        if(isClean)
        {
            return GREEN;
        }

        if(!isKnown)
        {
            return MAGENTA;
        }

        return RESET;
    }

    const std::string getSymbol() const
    {
        if(isTraversable || !isKnown)
        {
            return " ";
        }

        return "#";
    }
};
