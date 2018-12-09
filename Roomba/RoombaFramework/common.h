#pragma once
#include <cassert>
#include <cstdint>
#include <cstring>

class Coor
{
    friend class Rotation;

  public:
    Coor(int x, int y) : m_x(x), m_y(y){};
    Coor(const Coor& other) : m_x(other.m_x), m_y(other.m_y){};

    Coor operator+(const Coor& other) const { return Coor(m_x + other.m_x, m_y + other.m_y); }

  private:
    int m_x;
    int m_y;
};

class Rotation
{
  public:
    static Rotation Forward() { return Rotation(0); }
    static Rotation Right() { return Rotation(90); }
    static Rotation Backward() { return Rotation(180); }
    static Rotation Left() { return Rotation(270); }
    Rotation(uint32_t degrees)
    {
        static const int s_sin[4] = {0, 1, 0, -1};
        static const int s_cos[4] = {1, 0, -1, 0};

        m_matrix[0] = s_cos[degrees / 90 % 4];
        m_matrix[1] = -s_sin[degrees / 90 % 4];
        m_matrix[2] = s_cos[degrees / 90 % 4];
        m_matrix[3] = s_cos[degrees / 90 % 4];
    }

    Rotation(const Rotation& other) : Rotation(other.m_matrix, 4) {}

    // self * other
    Rotation mul(const Rotation& other)
    {
        int matrix[4];
        matrix[0] = m_matrix[0] * other.m_matrix[0] + m_matrix[1] * other.m_matrix[2];
        matrix[1] = m_matrix[0] * other.m_matrix[1] + m_matrix[1] * other.m_matrix[3];
        matrix[2] = m_matrix[2] * other.m_matrix[0] + m_matrix[3] * other.m_matrix[2];
        matrix[3] = m_matrix[2] * other.m_matrix[1] + m_matrix[3] * other.m_matrix[3];
        return Rotation(matrix, sizeof(matrix) / sizeof(matrix[0]));
    }

    Coor mul(const Coor& other)
    {
        return Coor(m_matrix[0] * other.m_x + m_matrix[1] * other.m_y,
                    m_matrix[2] * other.m_x + m_matrix[3] * other.m_y);
    }

  private:
    Rotation(const int* fill, const size_t count)
    {
        assert(count == sizeof(m_matrix) / sizeof(m_matrix[0]));
        memcpy(m_matrix, fill, sizeof(m_matrix));
    }
    int m_matrix[4];
};

class Pose
{
  public:
    Pose(const Coor& position, const Rotation& rotation) : m_pos(position), m_rot(rotation) {}
    Pose(const Coor& position) : Pose(position, Rotation::Forward()) {}
    Pose(const Rotation& rotation) : Pose(Coor(0, 0), rotation) {}

    Pose operator+(const Pose& pose)
    {
        Rotation r = m_rot.mul(pose.m_rot);
        Coor t = r.mul(pose.m_pos);
        return Pose(m_pos + t, r);
    }

  private:
    Coor m_pos;
    Rotation m_rot;
};
