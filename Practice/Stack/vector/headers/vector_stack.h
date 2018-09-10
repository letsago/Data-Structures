#pragma once

#include "myvector.h"

template <typename T>
class Stack
{
public:

    bool Pop()
    {
        if (m_vector.Length() == 0)
            return false;
        
        m_vector.Remove_back();
        
        return true;
    }

    bool Push(T value)
    {
        m_vector.Insert_back(value);
        
        return true;
    }

    T& Top()
    {
        return m_vector.Back();
    }

    const T& Top() const
    {
        return m_vector.Back();
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

    MyVector<T> m_vector;
};