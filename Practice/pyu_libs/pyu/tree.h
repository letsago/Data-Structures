#pragma once

#include "stack.h"
#include "vector.h"
#include "queue.h"

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

    uint32_t depth() const
    {
        if (m_root == nullptr)
        {
            return 0;
        }

        shared_ptr<LinearStorageInterface<Metadata>> pData(new Vector<Metadata>(size()));
        Queue<Metadata> order(pData);
        order.push({m_root, 1});
        uint32_t d;

        while (order.length() > 0)
        {
            Node* curr = order.front().m_node;
            d = order.front().m_val;
            order.pop();

            if (curr->m_left != nullptr)
            {
                order.push({curr->m_left, d + 1});
            }

            if (curr->m_right != nullptr)
            {
                order.push({curr->m_right, d + 1});
            }
        }

        return d;
    }

    friend std::ostream& operator<< (std::ostream& os, const Tree& tree)
    {
        uint32_t d = tree.depth();

        if (d > 0)
        {
            shared_ptr<LinearStorageInterface<Metadata>> pData(new Vector<Metadata>(tree.size()));
            Queue<Metadata> order(pData);

            uint32_t numSpaces = (1 << d) - 1;
            order.push({tree.m_root, numSpaces >> 1});
            Node* curr = order.front().m_node;
            uint32_t pos = order.front().m_val;
            uint32_t spacesBeforeEnd;   // used to increment appropriate spaces for child node positions and for appropriately inserting
                                        // spaces instead of values when navigating values queue

            if (d > 1)
            {
                spacesBeforeEnd = 1 << (d - 2);
            }
            else
                spacesBeforeEnd = 0;

            while (order.length() > 0)
            {
                for (uint32_t i = 0; i < numSpaces; ++i)
                {
                    if (i != pos || i == (numSpaces - spacesBeforeEnd))
                    {
                        os << ' ';

                        if (i == numSpaces - 1)
                            spacesBeforeEnd = spacesBeforeEnd >> 1;
                    }
                    else
                    {
                        os << order.front().m_node->m_value;
                        order.pop();

                        if (curr->m_left != nullptr)
                        {
                            order.push({curr->m_left, pos - spacesBeforeEnd});
                        }

                        if (curr->m_right != nullptr)
                        {
                            order.push({curr->m_right, pos + spacesBeforeEnd});
                        }

                        curr = order.front().m_node;
                        pos = order.front().m_val;
                    }
                }

                os << std::endl;
            }
        }

        return os;
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

    Vector<T> getSorted()
    {
        Vector<T> sorted(size());
        shared_ptr<LinearStorageInterface<Node*>> nodes(new Vector<Node*>(size()));
        Stack<Node*> stack(nodes);
        Node* curr = m_root;

        while (!stack.empty() || curr != nullptr)
        {
            while (curr != nullptr)
            {
                stack.push(curr);
                curr = curr->m_left;
            }

            curr = stack.top();
            stack.pop();
            sorted.insert_back(curr->m_value);
            curr = curr->m_right;
        }

        return sorted;
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

    struct Metadata
    {
        Node* m_node;
        uint32_t m_val;

        bool operator== (const Metadata& other) const
        {
            return (m_node == other.m_node && m_val == other.m_val);
        }
    };

    Node* m_root;
    uint32_t m_size;
};

}