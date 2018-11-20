#pragma once

#include "iterator.h"
#include "linked_list.h"
#include "shared_ptr.h"
#include "vector.h"
#include <stdexcept>

namespace pyu
{

template <typename K, typename V, typename F>
class UnorderedMap
{
  private:
    struct KeyValuePair
    {
        KeyValuePair(const K& key, const V& value) : m_key(key), m_pValue(shared_ptr<V>(new V(value))){};

        KeyValuePair(const K& key) : m_key(key), m_pValue(nullptr){};

        bool operator==(const KeyValuePair& other) const { return (m_key == other.m_key); }

        K m_key;
        shared_ptr<V> m_pValue;
    };

  public:
    UnorderedMap() : m_bucketSize(1), m_size(0) { m_map.resize(m_bucketSize); }

    size_t bucket_size() const { return m_bucketSize; }
    size_t size() const { return m_size; }

    bool empty() const { return (size() == 0); }

    bool insert(const K& key, const V& val)
    {
        uint64_t bucket = getBucket(key);

        if((m_map.at(bucket)).contains(KeyValuePair(key)))
        {
            at(key) = val;
            return false;
        }

        (m_map.at(bucket)).insert_front(KeyValuePair(key, val));

        while((m_map.at(bucket)).length() > kBucketDepth)
        {
            rebalance();
            bucket = getBucket(key);
        }

        ++m_size;
        return true;
    }

    bool remove(const K& key)
    {
        uint64_t bucket = getBucket(key);
        int keyPosition = (m_map.at(bucket)).find(KeyValuePair(key));

        if(keyPosition == -1)
        {
            return false;
        }

        (m_map.at(bucket)).remove(keyPosition);
        --m_size;
        return true;
    }

    void clear()
    {
        m_map.clear();
        m_size = 0;
        m_bucketSize = 1;
        m_map.resize(m_bucketSize);
    }

    V& at(const K& key) { return *((*((m_map.at(getBucket(key))).findIterator(KeyValuePair(key)))).m_pValue); }

    V& operator[](const K& key) { return at(key); }

    const V& at(const K& key) const
    {
        return *((*((m_map.at(getBucket(key))).findIterator(KeyValuePair(key)))).m_pValue);
    }

    const V& operator[](const K& key) const { return at(key); }

    bool contains(const K& key) const { return (find(key) != end()); }

    bool operator==(const UnorderedMap& other) const
    {
        if(size() != other.size())
        {
            return false;
        }

        for(Iterator<K> it = begin(); it != end(); ++it)
        {
            if(!other.contains(*it))
            {
                return false;
            }

            if(at(*it) != other.at(*it))
            {
                return false;
            }
        }

        return true;
    }

    Iterator<K> find(const K& key)
    {
        uint64_t bucket = getBucket(key);
        shared_ptr<IteratorNode<K>> node(new MapIteratorNode((m_map.at(bucket)).findIterator(KeyValuePair(key)), this));
        return node;
    }

    Iterator<K> begin()
    {
        shared_ptr<IteratorNode<K>> node(new MapIteratorNode((m_map.at(0)).begin(), this));
        return node;
    }

    Iterator<K> end()
    {
        shared_ptr<IteratorNode<K>> node(new MapIteratorNode((m_map.at(m_bucketSize - 1)).end(), this));
        return node;
    }

    Iterator<K> begin(uint32_t bucketNumber)
    {
        if(bucketNumber >= m_bucketSize)
        {
            throw std::out_of_range("bucket out of range");
        }

        shared_ptr<IteratorNode<K>> node(new BucketIteratorNode((m_map.at(bucketNumber)).begin()));
        return node;
    }

    Iterator<K> end(uint32_t bucketNumber)
    {
        if(bucketNumber >= m_bucketSize)
        {
            throw std::out_of_range("bucket out of range");
        }

        shared_ptr<IteratorNode<K>> node(new BucketIteratorNode((m_map.at(bucketNumber)).end()));
        return node;
    }

    const Iterator<K> find(const K& key) const
    {
        uint64_t bucket = getBucket(key);
        shared_ptr<IteratorNode<K>> node(new MapIteratorNode((m_map.at(bucket)).findIterator(KeyValuePair(key)), this));
        return node;
    }

    const Iterator<K> begin() const
    {
        shared_ptr<IteratorNode<K>> node(new MapIteratorNode((m_map.at(0)).begin(), this));
        return node;
    }

    const Iterator<K> end() const
    {
        shared_ptr<IteratorNode<K>> node(new MapIteratorNode((m_map.at(m_bucketSize - 1)).end(), this));
        return node;
    }

    const Iterator<K> begin(uint32_t bucketNumber) const
    {
        if(bucketNumber >= m_bucketSize)
        {
            throw std::out_of_range("bucket out of range");
        }

        shared_ptr<IteratorNode<K>> node(new BucketIteratorNode((m_map.at(bucketNumber)).begin()));
        return node;
    }

    const Iterator<K> end(uint32_t bucketNumber) const
    {
        if(bucketNumber >= m_bucketSize)
        {
            throw std::out_of_range("bucket out of range");
        }

        shared_ptr<IteratorNode<K>> node(new BucketIteratorNode((m_map.at(bucketNumber)).end()));
        return node;
    }

    static const uint32_t getBucketDepth() { return kBucketDepth; }

  private:
    class BucketIteratorNode : public IteratorNode<K>
    {
      public:
        BucketIteratorNode(Iterator<KeyValuePair> node) : m_curr(node){};

        K& value() { return (*m_curr).m_key; }

        const K& value() const { return (*m_curr).m_key; }

        BucketIteratorNode& next()
        {
            ++m_curr;
            return *this;
        }

        bool operator!=(const IteratorNode<K>& other) const
        {
            return m_curr != (dynamic_cast<const BucketIteratorNode&>(other).m_curr);
        }

      private:
        Iterator<KeyValuePair> m_curr;
    };

    class MapIteratorNode : public IteratorNode<K>
    {
      public:
        MapIteratorNode(Iterator<KeyValuePair> node, const UnorderedMap* map) : m_curr(node), m_src(map)
        {
            m_bucketCounter = 0;
            m_depth = 0;
        }

        K& value() { return (*m_curr).m_key; }

        const K& value() const { return (*m_curr).m_key; }

        MapIteratorNode& next()
        {
            ++m_curr;
            ++m_depth;

            if(m_depth > ((m_src->m_map).at(m_bucketCounter)).length() - 1)
            {
                ++m_bucketCounter;
                m_depth = 0;

                if(m_bucketCounter < m_src->m_bucketSize)
                {
                    m_curr = ((m_src->m_map).at(m_bucketCounter)).begin();
                }
            }

            return *this;
        }

        bool operator!=(const IteratorNode<K>& other) const
        {
            return m_curr != (dynamic_cast<const MapIteratorNode&>(other).m_curr);
        }

      private:
        Iterator<KeyValuePair> m_curr;
        const UnorderedMap* m_src;
        size_t m_bucketCounter;
        size_t m_depth;
    };

    void rebalance()
    {
        m_bucketSize *= 2;
        Vector<LinkedList<KeyValuePair>> newMap(m_bucketSize);

        for(uint32_t i = 0; i < m_bucketSize; ++i)
        {
            newMap.insert_back(LinkedList<KeyValuePair>());
        }

        for(uint32_t bucket = 0; bucket < m_bucketSize / 2; ++bucket)
        {
            uint32_t bucketDepth = (m_map.at(bucket)).length();

            for(uint32_t i = 0; i < bucketDepth; ++i)
            {
                const K& key = ((m_map.at(bucket)).front()).m_key;
                (m_map.at(bucket)).spliceFront(newMap.at(getBucket(key)));
            }
        }

        m_map = newMap;
    }

    uint64_t getBucket(const K& key) const { return kHashFunction(key) & (m_bucketSize - 1); }

    Vector<LinkedList<KeyValuePair>> m_map;
    size_t m_bucketSize;
    size_t m_size;
    static const uint32_t kBucketDepth = 3;
    static const F kHashFunction;
};

template <typename K, typename V, typename F>
const F UnorderedMap<K, V, F>::kHashFunction;

} // namespace pyu
