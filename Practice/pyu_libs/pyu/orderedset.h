#pragma once

#include "iterator.h"
#include "balancedtree.h"

namespace pyu
{

template <typename T>
class OrderedSet
{
public:
    OrderedSet() : m_btree(BalancedTree<T>()) {}

    size_t size() const
    {
        return m_btree.size();
    }

    bool empty() const
    {
        return (size() == 0);
    }

    bool insert(const T& val)
    {
        return m_btree.insert(val);
    }

    bool remove(const T& val)
    {
        return m_btree.remove(val);
    }

    void clear()
    {
        m_btree.clear();
    }

    bool contains(const T& val) const
    {
        return m_btree.contains(val);
    }

    bool operator== (const OrderedSet& other)
    {
        if (size() != other.size())
            return false;

        for (Iterator<T> it = other.begin(); it != other.end(); ++it)
        {
            if (!contains(*it))
                return false;
        }

        return true;
    }

    Iterator<T> find(const T& val) const
    {
        return m_btree.find(val);
    }

    Iterator<T> begin() const
    {
        return m_btree.begin();
    }

    Iterator<T> end() const
    {
        return m_btree.end();
    }

private:

    BalancedTree<T> m_btree;
};

}