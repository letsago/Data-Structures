#pragma once

#include <iostream>
#include "vector.h"

namespace pyu
{

template <typename T>
class LinkedList
{
    public: 

    LinkedList()
    {
        m_head = nullptr;
        m_size = 0;
    }

    ~LinkedList()
    {
        Clear();
    }

    LinkedList(const LinkedList& other)
    {
        m_head = nullptr;
        m_size = 0;
        *this = other;
    }

    LinkedList& operator= (const LinkedList &other)
    {
        Clear();

        for (uint32_t i = 0; i < other.m_size; ++i)
        {
            Insert(i, other.At(i));
        }

        return *this;
    }

    void Print()
    {
        Obj* temp = m_head;

        while(temp != nullptr)
        {
            std::cout << temp -> m_value << " ";
            temp = temp -> m_next;
        }

        std::cout << std::endl;
    }

    int Length() const
    {   
        return m_size;
    }

    bool isEmpty()
    {
        return (m_size == 0);
    }

    bool Insert(const uint32_t position, const T value)
    {
        if (position > m_size)
            return false;

        Obj* next = m_head;
        Obj* prev = nullptr;

        for (uint32_t i = 1; i <= position; ++i)
        {
            prev = next;
            next = prev -> m_next;
        }

        Obj* new_obj = new Obj(value, next);

        if (next == m_head)
        {
            m_head = new_obj;
        }
        else
        {
            prev -> m_next = new_obj;
        }

        ++m_size;

        return true;
    }

    bool Remove(const uint32_t position)
    {
        if (m_head == nullptr)
            return false;
        
        if (position > m_size - 1)
            return false;

        Obj* deleted = m_head;
        Obj* prev = nullptr;

        for (uint32_t i = 0; i < position; ++i)
        {
            prev = deleted;
            deleted = prev -> m_next;
        }

        if (deleted == m_head)
        {
            m_head = m_head -> m_next;
        }
        else
        {
            prev -> m_next = deleted -> m_next;
        }

        delete deleted;
        --m_size;

        return true;
    }

    bool Insert_front(const T value)
    {
        return Insert(0, value);
    }

    bool Remove_front()
    {
        return Remove(0);
    }

    bool Insert_back(const T value)
    {
        return Insert(m_size, value);
    }

    bool Remove_back()
    {
        return Remove(m_size - 1);
    }

    T& At(const uint32_t position)
    {
        Obj* current = m_head;

        for (uint32_t i = 0; i < position; ++i)
        {
            current = current -> m_next;
        }

        T& value = current -> m_value;
        
        return value;
    }

    const T& At(const uint32_t position) const
    {
        Obj* current = m_head;

        for (uint32_t i = 0; i < position; ++i)
        {
            current = current -> m_next;
        }

        T& value = current -> m_value;
        
        return value;
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
        return At(m_size - 1);
    }

    const T& Back() const
    {
        return At(m_size - 1);
    }

    int FindFirst(const T value) const
    {
        Obj* target = m_head;

        for (uint32_t i = 0; i < m_size; ++i)
        {
            if (target -> m_value == value)
                return i;

            target = target -> m_next;
        }

        return -1;
    }

    Vector<int> FindMany(const T value) const
    {
        Vector<int> indices;
        Obj* target = m_head;

        for (uint32_t i = 0; i < m_size; ++i)
        {
            if (target -> m_value == value)
                indices.Insert_back(i);
            
            target = target -> m_next;    
        }
        
        return indices;
    }

    void Clear()
    {   
        Obj* curr = m_head;
        Obj* next;

        while (curr != nullptr)
        {
            next = curr -> m_next;
            delete curr;
            curr = next;
        }

        m_head = nullptr;
        m_size = 0;
    }

    private:

    struct Obj
    {
        Obj(T value, Obj* next)
        {
            m_value = value;
            m_next = next;
        }

        T m_value;
        Obj* m_next;
    };

    uint32_t m_size;
    Obj* m_head;

};

}