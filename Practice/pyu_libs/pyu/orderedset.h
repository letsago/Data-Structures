#pragma once

#include "iterator.h"
#include "balancedtree.h"

namespace pyu
{

template <typename T>
class OrderedSet
{
public:
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
        return m_btree.operator==(other.m_btree);
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