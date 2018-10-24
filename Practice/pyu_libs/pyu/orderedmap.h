#pragma once

#include "iterator.h"
#include "balancedtree.h"

namespace pyu
{

template <typename K, typename V>
class OrderedMap
{
public:
    OrderedMap() : m_btree(BalancedTree<K>()) {}

    size_t size() const
    {
        return 0;
    }

    bool empty() const
    {
        return (size() == 0);
    }

    bool insert(const K& key, const V& val)
    {
        return false;
    }

    bool remove(const K& key)
    {
        return false;
    }

    void clear()
    {

    }

    V& at(const K& key)
    {
        return 0;
    }

    V& operator[] (const K& key)
    {
        return 0;
    }

    const V& at(const K& key) const
    {
        return 0;
    }

    const V& operator[] (const K& key) const
    {
        return 0;
    }

    bool contains(const K& key) const
    {
        return false;
    }

    bool operator== (const OrderedMap& other)
    {
        return false;
    }

    Iterator<K> find(const K& key) const
    {
        return Iterator<K>(nullptr);
    }

    Iterator<K> begin() const
    {
        return Iterator<K>(nullptr);
    }

    Iterator<K> end() const
    {
        return Iterator<K>(nullptr);
    }

private:
    BalancedTree<K> m_btree;
};

}