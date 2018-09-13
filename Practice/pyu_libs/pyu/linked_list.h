#pragma once

#include <iostream>
#include "vector.h"

namespace pyu
{

template <typename T>
class LinkedList : public LinearStorageInterface<T>
{
    public: 

    LinkedList()
    {
        m_head = nullptr;
        m_size = 0;
    }

    ~LinkedList()
    {
        clear();
    }

    LinkedList(const LinkedList& other)
    {
        m_head = nullptr;
        m_size = 0;
        *this = other;
    }

    LinkedList& operator= (const LinkedList &other)
    {
        clear();

        for (uint32_t i = 0; i < other.m_size; ++i)
        {
            insert(i, other.at(i));
        }

        return *this;
    }

    void print() const
    {
        Obj* temp = m_head;

        while(temp != nullptr)
        {
            std::cout << temp -> m_value << " ";
            temp = temp -> m_next;
        }

        std::cout << std::endl;
    }

    uint32_t length() const
    {   
        return m_size;
    }

    bool insert(const uint32_t position, const T value)
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

    bool remove(const uint32_t position)
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

    T& at(const uint32_t position)
    {
        Obj* current = m_head;

        for (uint32_t i = 0; i < position; ++i)
        {
            current = current -> m_next;
        }

        T& value = current -> m_value;
        
        return value;
    }

    const T& at(const uint32_t position) const
    {
        Obj* current = m_head;

        for (uint32_t i = 0; i < position; ++i)
        {
            current = current -> m_next;
        }

        T& value = current -> m_value;
        
        return value;
    }

    int find(const T value) const
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

    Vector<int> findmany(const T value) const
    {
        Vector<int> indices;
        Obj* target = m_head;

        for (uint32_t i = 0; i < m_size; ++i)
        {
            if (target -> m_value == value)
                indices.insert_back(i);
            
            target = target -> m_next;    
        }
        
        return indices;
    }

    void clear()
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