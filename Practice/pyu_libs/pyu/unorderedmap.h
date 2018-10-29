#pragma once

#include "vector.h"
#include "linked_list.h"
#include "iterator.h"
#include "shared_ptr.h"
#include <stdexcept>

namespace pyu
{

template <typename K, typename V>
class UnorderedMap
{
public:
    size_t bucket_size()
    {
        return 0;
    }
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
        throw std::out_of_range("key not found");
    }

    V& operator[] (const K& key)
    {
        throw std::out_of_range("key not found");
    }

    const V& at(const K& key) const
    {
        throw std::out_of_range("key not found");
    }

    const V& operator[] (const K& key) const
    {
        throw std::out_of_range("key not found");
    }

    bool contains(const K& key) const
    {
        return false;
    }

    bool operator== (const UnorderedMap& other) const
    {
        return false;
    }

    Iterator<K> find(const K& key)
    {
        return Iterator<K>(nullptr);
    }

    Iterator<K> begin()
    {
        return Iterator<K>(nullptr);
    }

    Iterator<K> end()
    {
        return Iterator<K>(nullptr);
    }

    Iterator<K> begin(uint32_t bucketNumber)
    {
        return Iterator<K>(nullptr);
    }

    Iterator<K> end(uint32_t bucketNumber)
    {
        return Iterator<K>(nullptr);
    }
};

}