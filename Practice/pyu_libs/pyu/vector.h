#pragma once

#include <iostream>

namespace pyu
{

template <typename T> 
class Vector
{
public:

    // Vector Constructors
    // Because we initialized our member variables, we use the default constructor
    Vector()
    {
        m_memory_size = 0;
        m_actual_size = 0;
        m_data = nullptr;
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
        Clear();
    }
    
    // Overloading Assignment
    Vector& operator= (const Vector &other)
    {
        T* new_data = new T[other.m_memory_size];
        for (uint32_t i = 0; i < other.m_actual_size; ++i)
            new_data[i] = other.m_data[i];

        Clear();
        m_actual_size = other.m_actual_size;
        m_memory_size = other.m_memory_size;
        m_data = new_data;

        // return the existing object so we can chain this operator ("this" is a pointer that points to itself)
        return *this;
    }

    // Member Functions
    void Print() const
    {
        // if user passed in a null pointer for array, bail out early!
        if (!m_data)
        {
            std::cout << "Can't print null pointer, bailing out" << std::endl;
            return;
        }

        for (int index = 0; index < m_actual_size; index++)
            std::cout << m_data[index];

        std::cout << std::endl;
    }

    bool Insert(const uint32_t position, T value)
    {
        // cannot insert past actual size of array
        if (position > m_actual_size)
            return false;
        
        uint32_t new_actual_size = m_actual_size + 1;

        if (m_actual_size == 0)
            Resize(1);
        else if (new_actual_size > m_memory_size)
            Resize(m_actual_size * c_capacity_ratio);

        for (uint32_t i = new_actual_size - 1; i > position; i--)
            m_data[i] = m_data[i - 1];
                
        m_data[position] = value;
        m_actual_size = new_actual_size;

        return true;
    }
    
    bool Remove(const uint32_t position)
    {
        if (position >= m_actual_size)
        {
            return false;   // remove fails if position exceeds actual size of vector
        }

        int new_actual_size = m_actual_size - 1;
        
        for (int i = position; i < new_actual_size; i++)
            m_data[i] = m_data[i + 1];
        
        m_actual_size = new_actual_size;

        return true;
    }
    
    T& At(const uint32_t position)
    {
        return m_data[position];   
    }
    
    const T& At(const uint32_t position) const
    {
        return m_data[position];   
    }

    T& Front()
    {
        return At(0);
    }

    const T& Front() const
    {
        return At(0);
    }
    
    T& Back()
    {
        return At(m_actual_size - 1);
    }

    const T& Back() const
    {
        return At(0);
    }
    
    T* Data()
    { 
        return m_data; 
    }

    const T* Data() const
    {
        return m_data;
    }

    int Length() const
    {
        return m_actual_size;
    }

    int Capacity() const
    {
        return m_memory_size;
    }

    void Resize(const uint32_t new_size)
    {
        int bound;
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

        for (int i = 0; i < bound; i++)
        {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;
    }

    void Clear()
    {
        delete[] m_data;
        m_data = nullptr;
        m_memory_size = 0;
        m_actual_size = 0;
    }
    
    // returns true if array is empty
    bool Empty() const
    {
        return (m_actual_size == 0);
    }
    
    bool Insert_back(T value) 
    {
        return Insert(m_actual_size, value);
    }
    
    bool Remove_back()
    {
        return Remove(m_actual_size - 1);
    }
    
    bool Insert_front(T value)
    {
        return Insert(0, value);
    }

    bool Remove_front()
    {
        return Remove(0);
    }

private: 

    // Member Variables
    const uint32_t c_capacity_ratio = 2;
    uint32_t m_memory_size;
    uint32_t m_actual_size;
    T* m_data;
};

}