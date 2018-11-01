#pragma once

#include "iterator.h"
#include "balancedtree.h"
#include "shared_ptr.h"

namespace pyu
{

template <typename K, typename V>
class OrderedMap
{
private:
    struct KeyValuePair
    {
        KeyValuePair(const K& key, const V& value) : m_key(key), m_pValue(shared_ptr<V>(new V(value))) {};

        KeyValuePair(const K& key) : m_key(key), m_pValue(nullptr) {};

        bool operator> (const KeyValuePair& other) const
        {
            return (m_key > other.m_key);
        }

        bool operator== (const KeyValuePair& other) const
        {
            return (m_key == other.m_key);
        }

        bool operator!= (const KeyValuePair& other) const
        {
            return !(m_key == other.m_key);
        }

        K m_key;
        shared_ptr<V> m_pValue;
    };

public:
    size_t size() const
    {
        return m_btree.size();
    }

    bool empty() const
    {
        return (size() == 0);
    }

    bool insert(const K& key, const V& val)
    {
        if (!m_btree.insert(KeyValuePair(key, val)))
        {
            at(key) = val;
            return false;
        }
        else
            return true;
    }

    bool remove(const K& key)
    {
        return m_btree.remove(KeyValuePair(key));
    }

    void clear()
    {
        m_btree.clear();
    }

    V& at(const K& key)
    {
        return *((*(m_btree.find(KeyValuePair(key)))).m_pValue);
    }

    V& operator[] (const K& key)
    {
        return at(key);
    }

    const V& at(const K& key) const
    {
        return *((*(m_btree.find(KeyValuePair(key)))).m_pValue);
    }

    const V& operator[] (const K& key) const
    {
        return at(key);
    }

    bool contains(const K& key) const
    {
        return m_btree.contains(KeyValuePair(key));
    }

    bool operator== (const OrderedMap& other) const
    {
        if (size() != other.size())
            return false;

        Iterator<K> compare = other.begin();

        for (Iterator<K> it = begin(); it != end(); ++it)
        {
            if (*it != *compare)
                return false;

            if (at(*it) != other.at(*it))
                return false;

            ++compare;
        }

        return true;
    }

    Iterator<K> find(const K& key)
    {
        shared_ptr<IteratorNode<K>> node(new OrderedMapIteratorNode(m_btree.find(KeyValuePair(key))));
        return node;
    }

    Iterator<K> begin()
    {
        shared_ptr<IteratorNode<K>> node(new OrderedMapIteratorNode(m_btree.begin()));
        return node;
    }

    Iterator<K> end()
    {
        shared_ptr<IteratorNode<K>> node(new OrderedMapIteratorNode(m_btree.end()));
        return node;
    }

    const Iterator<K> find(const K& key) const
    {
        shared_ptr<IteratorNode<K>> node(new OrderedMapIteratorNode(m_btree.find(KeyValuePair(key))));
        return node;
    }

    const Iterator<K> begin() const
    {
        shared_ptr<IteratorNode<K>> node(new OrderedMapIteratorNode(m_btree.begin()));
        return node;
    }

    const Iterator<K> end() const
    {
        shared_ptr<IteratorNode<K>> node(new OrderedMapIteratorNode(m_btree.end()));
        return node;
    }

private:
    class OrderedMapIteratorNode : public IteratorNode<K>
    {
    public:
        OrderedMapIteratorNode(Iterator<KeyValuePair> node) : m_curr(node) {};

        K& value()
        {
            return (*m_curr).m_key;
        }

        const K& value() const
        {
            return (*m_curr).m_key;
        }

        OrderedMapIteratorNode& next()
        {
            ++m_curr;
            return *this;
        }

        bool operator!= (const IteratorNode<K>& other) const
        {
            return m_curr != (dynamic_cast<const OrderedMapIteratorNode&>(other).m_curr);
        }

    private:
        Iterator<KeyValuePair> m_curr;
    };

    BalancedTree<KeyValuePair> m_btree;
};

}
