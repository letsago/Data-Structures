#pragma once

#include "vector.h"

namespace pyu
{

template <typename T>
class Queue
{
public:

    bool Pop()
    {
        if (m_vector.Length() == 0)
            return false;
        
        m_vector.Remove_front();

        return true;
    }

    bool Push(T value)
    {
        m_vector.Insert_back(value);

        return true;
    }

    T& Front()
    {
        return m_vector.Front();
    }

    const T& Front() const
    {
        return m_vector.Front();
    }  

    int size() const
    {
        return m_vector.Length();
    }

    bool isEmpty()
    {
        return (m_vector.Empty());
    }

    void Clear()
    {
        m_vector.Clear();
    } 

private:

    Vector<T> m_vector;
};

}