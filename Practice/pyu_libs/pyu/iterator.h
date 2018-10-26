#pragma once

#include "shared_ptr.h"

namespace pyu
{

template <typename T>
class IteratorNode
{
    public:
        // adding virtual functionality that will be called in each child IteratorNode class
        // this functionality will then be implemented in class Iterator
        virtual T& value() const = 0;
        virtual IteratorNode& next() = 0;
        virtual bool operator!= (const IteratorNode& other) const = 0;
        virtual ~IteratorNode() {};
};

template <typename T>
class Iterator
{
    public:
        Iterator(shared_ptr<IteratorNode<T>> start)
        {
            m_curr = start;
        }

        T& operator* () const
        {
            return m_curr->value();
        }

        Iterator& operator++ ()
        {
            m_curr->next();
            return *this;
        }

        Iterator& operator+ (uint32_t x)
        {
            for (uint32_t i = 0; i < x; ++i)
                m_curr->next();

            return *this;
        }

        bool operator!= (const Iterator& other) const
        {
            return *m_curr != *(other.m_curr);
        }

        bool operator== (const Iterator& other) const
        {
            return !(*this != other);
        }

    private:
        shared_ptr<IteratorNode<T>> m_curr;
};

}