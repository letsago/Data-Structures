#pragma once

#include "stack.h"
#include "vector.h"

namespace pyu
{

template <typename T>
class Tree
{
    public:

    Tree()
    {
        m_root = nullptr;
        m_size = 0;
    }

    ~Tree()
    {
        clear();
    }

    uint32_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return (size() == 0);
    }

    bool insert(const T& val)
    {
        Node* next = m_root;
        Node* curr = nullptr;

        while (next != nullptr)
        {
            curr = next;

            if (curr->m_value == val)
                return false;

            if (curr->m_value < val)
                next = curr->m_right;
            else
                next = curr->m_left;
        }

        Node* node = new Node(val, nullptr, nullptr);

        if (curr == nullptr)
            m_root = node;
        else
        {
            if (curr->m_value < val)
                curr->m_right = node;
            else
                curr->m_left = node;
        }

        ++m_size;
        return true;
    }

    bool remove(const T& val)
    {
        if (empty())
            return false;

        Node* prev = nullptr;
        Node* curr = m_root;
        Node* next = nullptr;

        while (curr->m_value != val)
        {
            if (curr->m_left == nullptr && curr->m_right == nullptr)
                return false;

            prev = curr;
            if (val > prev->m_value)
                curr = prev->m_right;
            else
                curr = prev->m_left;
        }

        next = curr->m_left;

        if (curr != m_root)
        {
            if (prev->m_value > curr->m_value)
                prev->m_left = next;
            else
                prev->m_right = next;
        }
        else
            m_root = next;

        while (next != nullptr)
        {
            prev = next;
            next = prev->m_right;
        }

        if (curr->m_right != nullptr)
            prev->m_right = curr->m_right;

        delete curr;
        --m_size;
        return true;
    }

    void clear()
    {
        if (m_root != nullptr)
        {
            shared_ptr<LinearStorageInterface<Node*>> pdata(new Vector<Node*>(size()));
            Stack<Node*> deleteorder(pdata);
            deleteorder.push(m_root);

            while (deleteorder.length() > 0)
            {
                Node* curr = deleteorder.top();
                deleteorder.pop();

                if (curr->m_left)
                    deleteorder.push(curr->m_left);

                if (curr->m_right)
                    deleteorder.push(curr->m_right);

                delete curr;
            }
        }

        m_size = 0;
        m_root = nullptr;
    }

    bool contains(const T& val) const
    {
        Node* curr = m_root;

        while (true)
        {
            if (curr == nullptr)
                return false;

            if (val == curr->m_value)
                return true;

            if (val > curr->m_value)
                curr = curr->m_right;
            else
                curr = curr->m_left;
        }
    }

    private:

    struct Node
    {
        Node(const T& value, Node* right, Node* left)
        {
            m_value = value;
            m_right = right;
            m_left = left;
        }

        T m_value;
        Node* m_right;
        Node* m_left;
    };

    Node* m_root;
    uint32_t m_size;

};

}