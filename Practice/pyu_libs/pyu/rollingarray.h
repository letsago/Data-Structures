#pragma once

#include <iostream>
#include <algorithm>
#include "linear_storage_interface.h"

namespace pyu
{

template <typename T, const uint32_t N> 
class RollingArray : public LinearStorageInterface<T>
{
public:

    RollingArray()
    {
        m_size = 0;
        m_head = 0;
        m_data = new T[N];
    }

    RollingArray(const RollingArray& other)
    {
        m_size = 0;
        m_head = 0;
        m_data = nullptr;
        *this = other;
    }

    RollingArray& operator= (const RollingArray& other)
    {
        T* new_data = new T[N];
        m_head = other.m_head;
        m_size = other.m_size;
        uint32_t new_index = 0;
        for (uint32_t i = m_head; i < m_size; ++i)
        {
            new_data[new_index] = other.m_data[i];
            ++new_index;
        }

        for (uint32_t i = 0; i < m_head; ++i)
        {
            new_data[new_index] = other.m_data[i];
            ++new_index;
        }
            
        delete[] m_data;
        m_data = new_data;
        m_head = 0;

        return *this;
    }

    ~RollingArray()
    {
        clear();
        delete[] m_data;
        m_data = nullptr;
    }

    void print(std::ostream& os) const
    {
        for (uint32_t index = m_head; index < m_size; ++index)
            os << at(index) << " ";

        for (uint32_t index = 0; index < m_head; ++index)
            os << at(index) << " ";

        os << std::endl;
    }

    bool insert(const uint32_t position, const T value)
    {
        if (position != m_size)
            return false;

        uint32_t new_size = m_size + 1;
        
        if (new_size > N)
            return false;

        uint32_t pos = (m_head + m_size) % N;
        m_data[pos] = value;

        m_size = new_size;

        return true;
    }
    
    bool remove(const uint32_t position)
    {
        if (position != 0)
            return false;

        if (m_size == 0)
            return false;

        --m_size;
        m_head = (m_head + 1) % N;

        return true;
    }
    
    T& at(const uint32_t position)
    {
        return m_data[m_head];   
    }
    
    const T& at(const uint32_t position) const
    {
        return m_data[m_head];   
    }

    int find(const T value) const
    {
        uint32_t end = std::min((m_head + m_size), N);
        uint32_t counter = 0;

        for (uint32_t i = m_head; i < end; ++i)
        {
            if (m_data[i] == value)
                return (i - m_head);
            
            ++counter;
        }

        if ((m_head + m_size) > N)
        {
            for (uint32_t i = 0; i < (m_head + m_size) % N; ++i)
            {
                if (m_data[i] == value)
                    return counter;
                
                ++counter;
            }
        }

        return -1;
    }

    uint32_t length() const
    {
        return m_size;
    }

    uint32_t capacity() const
    {
        return N;
    }

    void clear()
    {
        m_size = 0;
        m_head = 0;
    }
    
private: 

    // Member Variables
    uint32_t m_head;
    uint32_t m_size;
    T* m_data;
};

}