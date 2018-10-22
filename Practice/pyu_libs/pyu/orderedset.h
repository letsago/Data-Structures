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
        return 0;
    }

    bool empty() const
    {
        return (size() == 0);
    }

    bool insert(const T& val)
    {
        return false;
    }

    bool remove(const T& val)
    {
        return false;
    }

    void clear()
    {

    }

    bool contains(const T& val) const
    {
        return false;
    }

    bool operator== (const OrderedSet& other)
    {
        return false;
    }

    Iterator<T> find(const T& val) const
    {
        return Iterator<T>(nullptr);
    }

    Iterator<T> begin() const
    {
        return Iterator<T>(nullptr);
    }

    Iterator<T> end() const
    {
        return Iterator<T>(nullptr);
    }

private:
    BalancedTree<T> m_btree;
};

}