#pragma once

#include "linear_storage_interface.h"

namespace pyu
{

template <typename T>
class Queue
{

public:

    Queue(pyu::LinearStorageInterface<T>** ppLsi)
    {
        m_pLsi = *ppLsi;
        *ppLsi = nullptr;
    }

    ~Queue()
    {
        delete m_pLsi;
    }

    bool pop()
    {   
        return m_pLsi->remove_front();
    }

    bool push(T value)
    {
        return m_pLsi->insert_back(value);
    }

    T& front()
    {
        return m_pLsi->front();
    }

    const T& front() const
    {
        return m_pLsi->front();
    }  

    int length() const
    {
        return m_pLsi->length();
    }

    bool empty()
    {
        return m_pLsi->empty();
    }

    void clear()
    {
        m_pLsi->clear();
    } 

private:

    LinearStorageInterface<T>* m_pLsi;
};

}