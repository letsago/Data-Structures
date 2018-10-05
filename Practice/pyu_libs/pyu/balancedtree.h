#pragma once

#include "tree.h"

namespace pyu
{

template <typename T>
class BalancedTree : public Tree<T>
{
    public:

    BalancedTree()
    {
        m_root = nullptr;
        m_size = 0;
    }

    ~BalancedTree()
    {
        Tree<T>::clear();
    }

    bool insert(const T& val)
    {
        return true;
    }

    bool remove()
    {
        return true;
    }

    private:

    void balance()
    {
        return true;
    }

    struct Node
    {
        Node(const T& value, Node* right, Node* left, Node* parent)
        {
            m_value = value;
            m_right = right;
            m_left = left;
            m_parent = parent;
        }

        T m_value;
        Node* m_right;
        Node* m_left;
        Node* m_parent;
    };

    struct Metadata
    {
        Node* m_node;
        uint32_t m_val;

        bool operator== (const Metadata& other) const
        {
            return (m_node == other.m_node && m_val == other.m_val);
        }
    };

    struct PrintMetadata
    {
        Node* m_node;
        std::string m_str;
        uint32_t m_row;
        double m_relCol;
    };

    Node* m_root;
    uint32_t m_size;
};

}