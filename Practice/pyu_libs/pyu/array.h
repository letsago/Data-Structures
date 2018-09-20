#pragma once

#include <iostream>
#include "linear_storage_interface.h"

namespace pyu
{

template <typename T, const uint32_t N> 
class Array : public LinearStorageInterface<T>
{
public:

    Array()
    {
        m_size = 0;
        m_data = new T[N];
    }

    Array(const Array& other)
    {
        m_data = new T[N];
        *this = other;
    }

    Array& operator= (const Array& other)
    {
        for (uint32_t i = 0; i < other.m_size; ++i)
            m_data[i] = other.m_data[i];

        m_size = other.m_size;

        return *this;
    }

    ~Array()
    {
        clear();
        delete[] m_data;
        m_data = nullptr;
    }

    void print(std::ostream& os) const
    {
        for (uint32_t i = 0; i < m_size; ++i)
            os << at(i) << " ";
        
        os << std::endl;
    }

    bool insert(const uint32_t position, const T value)
    {
        // cannot insert past actual size of array
        if (position > m_size)
            return false;

        uint32_t new_size = m_size + 1;
        
        if (new_size > N)
            return false;

        for (uint32_t i = new_size - 1; i > position; i--)
            m_data[i] = m_data[i - 1];
                
        m_data[position] = value;
        m_size = new_size;

        return true;
    }
    
    bool remove(const uint32_t position)
    {
        if (position >= m_size)
            return false;   // remove fails if position exceeds actual size of Array

        --m_size;
        
        for (uint32_t i = position; i < m_size; i++)
            m_data[i] = m_data[i + 1];

        return true;
    }
    
    T& at(const uint32_t position)
    {
        return m_data[position];   
    }
    
    const T& at(const uint32_t position) const
    {
        return m_data[position];   
    }

    int find(const T value) const
    {
        for (uint32_t i = 0; i < length(); ++i)
        {
            if (at(i) == value)
                return i;
        }

        return -1;
    }
    
    T* data()
    { 
        return m_data; 
    }

    const T* data() const
    {
        return m_data;
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
    }
    
private: 

    // Member Variables
    uint32_t m_size;
    T* m_data;
};

}