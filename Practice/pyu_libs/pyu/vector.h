#pragma once

#include <iostream>
#include "linear_storage_interface.h"

namespace pyu
{

template <typename T> 
class Vector : public LinearStorageInterface<T>
{
public:

    // Vector Constructors
    // Because we initialized our member variables, we use the default constructor
    Vector(const int capacity = 0)
    {
        m_actual_size = 0;
        m_memory_size = capacity;
        m_data = new T[m_memory_size];
    }
    
    // Constructor for pre-populating vector with array of characters
    Vector(const T * input, const int size)
    {
        m_actual_size = size;
        m_memory_size = size;
        m_data = new T[m_memory_size];
        
        for (uint32_t index = 0; index < m_actual_size; index++)
        {
            m_data[index] = input[index];
        }
    }

    // Copy Constructor using the = overloaded assignment where *this (reference) is assigned to Vector& other
    Vector(const Vector& other)
    {
        m_memory_size = 0;
        m_actual_size = 0;
        m_data = nullptr;
        *this = other;
    }

    // Deconstructor that clears Vector when function goes out of scope
    ~Vector()
    {
        clear();
    }
    
    // Overloading Assignment
    Vector& operator= (const Vector &other)
    {
        T* new_data = new T[other.m_memory_size];
        for (uint32_t i = 0; i < other.m_actual_size; ++i)
            new_data[i] = other.m_data[i];

        clear();
        m_actual_size = other.m_actual_size;
        m_memory_size = other.m_memory_size;
        m_data = new_data;

        // return the existing object so we can chain this operator ("this" is a pointer that points to itself)
        return *this;
    }

    void print(std::ostream& os) const
    {
        for (uint32_t i = 0; i < m_actual_size; ++i)
            os << at(i) << " ";

        os << std::endl;
    }

    // Member Functions
    bool insert(const uint32_t position, const T value)
    {
        // cannot insert past actual size of array
        if (position > m_actual_size)
            return false;
        
        uint32_t new_actual_size = m_actual_size + 1;

        if (m_actual_size == 0)
            resize(1);
        else if (new_actual_size > m_memory_size)
            resize(m_actual_size * c_capacity_ratio);

        for (uint32_t i = new_actual_size - 1; i > position; i--)
            m_data[i] = m_data[i - 1];
                
        m_data[position] = value;
        m_actual_size = new_actual_size;

        return true;
    }
    
    bool remove(const uint32_t position)
    {
        if (position >= m_actual_size)
        {
            return false;   // remove fails if position exceeds actual size of vector
        }

        uint32_t new_actual_size = m_actual_size - 1;
        
        for (uint32_t i = position; i < new_actual_size; i++)
            m_data[i] = m_data[i + 1];
        
        m_actual_size = new_actual_size;

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
        return m_actual_size;
    }

    uint32_t capacity() const
    {
        return m_memory_size;
    }

    void resize(const uint32_t new_size)
    {
        uint32_t bound;
        m_memory_size = new_size;
        T* new_data = new T[m_memory_size];
        if (new_size > m_actual_size)
        {
            bound = m_actual_size;
        }
        else
        {
            bound = m_memory_size;
            m_actual_size = m_memory_size;
        }

        for (uint32_t i = 0; i < bound; i++)
        {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;
    }

    void clear()
    {
        delete[] m_data;
        m_data = nullptr;
        m_memory_size = 0;
        m_actual_size = 0;
    }
    
private: 

    // Member Variables
    const uint32_t c_capacity_ratio = 2;
    uint32_t m_memory_size;
    uint32_t m_actual_size;
    T* m_data;
};

}