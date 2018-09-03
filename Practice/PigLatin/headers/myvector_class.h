#pragma once

#include <iostream>
#include <limits>
using namespace std;

template <typename T> 
class MyVector
{
public:

    // MyVector Constructors
    // Because we initialized our member variables, we use the default constructor
    MyVector()
    {
        memory_size = 0;
        actual_size = 0;
        m_data = nullptr;
    }
    
    // Constructor for pre-populating vector with array of characters
    MyVector(const T * input, const int size)
    {
        actual_size = size;
        memory_size = 10 * actual_size;
        T *new_data = new T[memory_size];
        for (int index = 0; index < actual_size; index++)
            new_data[index] = input[index];
        m_data = new_data;
    }

    // Copy Constructor using the = overloaded assignment where *this (reference) is assigned to MyVector& other
    MyVector(const MyVector& other)
    {
        *this = other;
    }

    // Deconstructor that clears MyVector when function goes out of scope
    ~MyVector()
    {
        Clear();
    }
    
    // Overloading Assignment
    MyVector& operator= (const MyVector &other)
    {
        T *new_data = new T[other.memory_size];
        for (int index = 0; index < other.actual_size; index++)
            new_data[index] = other.At(index);
        Clear();
        m_data = new_data;
        actual_size = other.actual_size;
        memory_size = other.memory_size;

        // return the existing object so we can chain this operator ("this" is a pointer that points to itself)
        return *this;
    }

    // Member Functions
    void Print() const
    {
        // if user passed in a null pointer for array, bail out early!
        if (!m_data)
        {
            cout << "Can't print null pointer, bailing out" << endl;
            return;
        }

        for (int index = 0; index < actual_size; index++)
            cout << m_data[index];

        cout << endl;
    }

    bool Insert(const unsigned int position, T value)
    {
        int new_memory_size;
        int new_actual_size;
        bool isIndexBiggerthanMemorySize = false;
        bool isIndexBiggerthanActualSize = false;

        if (position >= memory_size)
        {
            if (position > numeric_limits<int>::max() / 10) // fails to insert if position exceeds order of magnitude within max integer limit
                return false;

            new_memory_size = (position + 1) * 10;
            new_actual_size = position + 1;
            isIndexBiggerthanMemorySize = true;
        }
        else
        {
            if (position >= actual_size)
            {
                isIndexBiggerthanActualSize = true;
                new_actual_size = position + 1;
            }
            else
            {
                new_actual_size = actual_size + 1;
            }
            new_memory_size = memory_size;       
        }

        if (isIndexBiggerthanMemorySize)
        {
            T *new_data = new T[new_memory_size];
            for (int i = 0; i < new_actual_size - 1; i++)
            {
                if (i < actual_size)
                    new_data[i] = m_data[i];
                else
                    new_data[i] = 0;
            }
            new_data[new_actual_size - 1] = value;

            Clear();
            m_data = new_data;
        }
        else
        {
            if (isIndexBiggerthanActualSize)
            {
                for (int i = actual_size; i < new_actual_size - 1; i++)
                    m_data[i] = 0;
                
                m_data[new_actual_size - 1] = value;
            }
            else
            {
                for (int i = new_actual_size - 1; i > position; i--)
                    m_data[i] = m_data[i - 1];

                m_data[position] = value;
            }
        }
        memory_size = new_memory_size;
        actual_size = new_actual_size;
        return true;
    }
    
    bool Remove(const unsigned int position)
    {
        if (position >= actual_size)
        {
            return false;   // remove fails if position exceeds actual size of vector
        }

        int new_actual_size = actual_size - 1;
        
        for (int i = position; i < new_actual_size; i++)
            m_data[i] = m_data[i + 1];
        
        actual_size = new_actual_size;

        return true;
    }
    
    T& At(const unsigned int position)
    {
        return m_data[position];   
    }
    
    const T& At(const unsigned int position) const
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
        return At(actual_size - 1);
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
        return actual_size;
    }

    void Clear()
    {
        delete[] m_data;
        m_data = nullptr;
        memory_size = 0;
        actual_size = 0;
    }
    
    // returns true if array is empty
    bool Empty() const
    {
        return (memory_size == 0);
    }
    
    void Insert_back(T value) 
    {
        Insert(actual_size, value);
    }
    
    void Remove_back()
    {
        Remove(actual_size - 1);
    }
    
    void Insert_front(T value)
    {
        Insert(0, value);
    }

    void Remove_front()
    {
        Remove(0);
    }

private: 

    // Member Variables
    int memory_size;
    int actual_size;
    T* m_data;
};
