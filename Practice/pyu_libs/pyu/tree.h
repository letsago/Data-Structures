#pragma once

#include "stack.h"
#include "vector.h"
#include "queue.h"
#include <string>
#include <algorithm>
#include <cmath>

namespace pyu
{

template <typename T>
class Tree
{
public:
    Tree() : m_root(nullptr), m_size(0), m_depth(0), m_depthCounter(0) {};

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
        return insertNode(val);
    }

    bool remove(const T& val)
    {
        return removeNode(val);
    }

    uint32_t depth() const
    {
        return m_depth;
    }

    friend std::ostream& operator<< (std::ostream& os, const Tree& tree)
    {
        if (tree.m_root)
        {
            Vector<PrintMetadata> printData(tree.size());
            Queue<uint32_t> order(new Vector<uint32_t>(tree.size()));
            printData.insert_back({tree.m_root, std::to_string(tree.m_root->m_value), 1, 0});
            order.push(printData.length() - 1);
            uint32_t numSpaces = 3;
            double minRelCol = 0;
            double maxRelCol = 0;

            auto addNode = [&printData, &order, &numSpaces](const PrintMetadata& obj, Node* next, double colDelta)
            {
                printData.insert_back({
                        next,
                        std::to_string(next->m_value),
                        obj.m_row + 3,
                        obj.m_relCol + colDelta});
                order.push(printData.length() - 1);
                numSpaces = std::max(numSpaces, static_cast<uint32_t>(printData.back().m_str.length()));
            };

            while (order.length() > 0)
            {
                const PrintMetadata obj = printData.at(order.front());
                order.pop();
                double relColDiff = 1.0 / (1 << ((obj.m_row + 2) / 3));
                minRelCol = std::min(minRelCol, obj.m_relCol);
                maxRelCol = std::max(maxRelCol, obj.m_relCol);

                if (obj.m_node->m_children[RIGHT])
                    addNode(obj, obj.m_node->m_children[RIGHT], relColDiff);

                if (obj.m_node->m_children[LEFT])
                    addNode(obj, obj.m_node->m_children[LEFT], -relColDiff);
            }

            uint32_t depth = (printData.back().m_row + 2) / 3;
            uint32_t normFactor = 1 << (depth - 1);
            uint32_t transFactor = normFactor * std::abs(minRelCol);
            uint32_t maxCol = maxRelCol * normFactor + transFactor;
            uint32_t lineCounter;
            uint32_t prevRow = 0;

            if (depth > 1)
                lineCounter = (1 << (depth - 2)) - 1;
            else
                lineCounter = 0;

            std::string row (numSpaces * (maxCol + 1), ' ');
            row.append("\n");
            row = row + row + row;
            std::string output;

            for (uint32_t i = 0; i < printData.length(); ++i)
            {
                if (prevRow != printData.at(i).m_row)
                {
                    os << output;
                    output = row;

                    if (i != 0)
                        lineCounter = lineCounter >> 1;
                }

                uint32_t pos = (printData.at(i).m_relCol * normFactor + transFactor) * numSpaces + (numSpaces - printData.at(i).m_str.length()) / 2;
                output.replace(pos, printData.at(i).m_str.length(), printData.at(i).m_str);

                if (printData.at(i).m_node->m_children[LEFT] || printData.at(i).m_node->m_children[RIGHT])
                {
                    uint32_t arrowPos = (numSpaces * (maxCol + 1) + 1) + (printData.at(i).m_relCol * normFactor + transFactor) * numSpaces + numSpaces / 2;
                    output.replace(arrowPos, 1, "|");

                    int numLines = lineCounter * numSpaces + numSpaces / 2 - 1;

                    std::string lines;
                    for (int i = 0; i < numLines; ++i)
                        lines += "_";

                    const uint32_t position = (numSpaces * (maxCol + 1) + 1) + arrowPos;

                    if (printData.at(i).m_node->m_children[LEFT])
                    {
                        output.replace(arrowPos - numLines, numLines, lines);
                        output.replace(position - numLines - 1, 1, "/");
                    }

                    if (printData.at(i).m_node->m_children[RIGHT])
                    {
                        output.replace(arrowPos + 1, numLines, lines);
                        output.replace(position + numLines + 1, 1, "\\");
                    }
                }

                prevRow = printData.at(i).m_row;
            }

            output.erase(output.begin() + numSpaces * (maxCol + 1) + 1, output.end());
            os << output;
        }

        return os;
    }

    void clear()
    {
        if (m_root)
        {
            Stack<Node*> deleteorder(new Vector<Node*>(size()));
            deleteorder.push(m_root);

            while (deleteorder.length() > 0)
            {
                Node* curr = deleteorder.top();
                deleteorder.pop();

                for (uint32_t i = 0; i < sizeof(curr->m_children)/sizeof(curr->m_children[0]); ++i)
                {
                    if (curr->m_children[i])
                        deleteorder.push(curr->m_children[i]);
                }

                delete curr;
            }
        }

        m_size = 0;
        m_depth = 0;
        m_depthCounter = 0;
        m_root = nullptr;
    }

    bool contains(const T& val) const
    {
        return find(val);
    }

    Vector<T> getSorted() const
    {
        Vector<T> sorted(size());
        Stack<Node*> stack(new Vector<Node*>(size()));
        Node* curr = m_root;

        while (!stack.empty() || curr)
        {
            while (curr)
            {
                stack.push(curr);
                curr = curr->m_children[LEFT];
            }

            curr = stack.top();
            stack.pop();
            sorted.insert_back(curr->m_value);
            curr = curr->m_children[RIGHT];
        }

        return sorted;
    }

    bool isBalanced() const
    {
        if (empty())
            return true;

        return (static_cast<uint32_t>(1 << (depth() - 1)) <= size());
    }

protected:
    enum Direction
    {
        LEFT,
        RIGHT
    };

    struct Node
    {
        Node(const T& value)
        {
            memset(m_children, 0, sizeof(m_children));
            m_value = value;
        }

        virtual ~Node() {}

        virtual void reset()
        {
            memset(m_children, 0, sizeof(m_children));
        }

        virtual void connect(Node* conNode, Direction dir)
        {
            m_children[dir] = conNode;
        }

        virtual void replace(Node* node, Node* parent)
        {
            if (parent)
                parent->connect(m_children[m_value > node->m_value], static_cast<Direction>(m_value > parent->m_value));

            this->reset();

            for (uint32_t i = 0; i < sizeof(m_children)/sizeof(m_children[0]); ++i)
                m_children[i] = node->m_children[i];
        }

        T m_value;
        Node* m_children[2];
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

    Node* find(const T& val, Node** pPrev = nullptr, uint32_t* pDepth = nullptr) const
    {
        Node* curr = m_root;
        uint32_t dummyDepth = 1;
        Node* dummyPrev = nullptr;

        while (curr && curr->m_value != val)
        {
            dummyPrev = curr;
            curr = curr->m_children[(val > curr->m_value)];
            ++dummyDepth;
        }

        if (pDepth)
            *pDepth = dummyDepth;

        if (pPrev)
            *pPrev = dummyPrev;

        return curr;
    }

    Node* insertNode(const T& val, Node** pPrev = nullptr)
    {
        Node* dummyPrev = nullptr;
        uint32_t newNodeDepth = 0;

        if (find(val, &dummyPrev, &newNodeDepth))
            return nullptr;

        if (newNodeDepth == m_depth)
            ++m_depthCounter;
        else if (newNodeDepth > m_depth)
        {
            m_depthCounter = 1;
            m_depth = newNodeDepth;
        }

        Node* node = createNode(val);

        if (!m_root)
            m_root = node;
        else
            dummyPrev->connect(node, static_cast<Direction>(val > dummyPrev->m_value));

        if (pPrev)
            *pPrev = dummyPrev;

        ++m_size;
        return node;
    }

    void nodeSwap(Node* oldRoot, Node* oldRootParent, Node* newRoot, Node* newRootParent)
    {
        if (newRoot)
            newRoot->replace(oldRoot, newRootParent);

        oldRoot->reset();

        if (oldRoot == m_root)
            m_root = newRoot;
        else
            oldRootParent->connect(newRoot, static_cast<Direction>(oldRoot->m_value > oldRootParent->m_value));
    }

    Node* findNewRoot(const Node* oldRoot, Node*& newRootParent, uint32_t& newRootDepth) const
    {
        Node* newRoot = nullptr;
        newRootParent = const_cast<Node*>(oldRoot);

        auto setNewRoot = [&newRootParent, &newRoot, &oldRoot, &newRootDepth](const Direction dir)
        {
            newRoot = oldRoot->m_children[dir];
            ++newRootDepth;
            while (newRoot->m_children[!dir])
            {
                newRootParent = newRoot;
                newRoot = newRoot->m_children[!dir];
                ++newRootDepth;
            }
        };

        if (oldRoot->m_children[LEFT])
            setNewRoot(LEFT);
        else if (oldRoot->m_children[RIGHT])
            setNewRoot(RIGHT);

        return newRoot;
    }

    bool removeNode(const T& val)
    {
        Node* oldRootParent = nullptr;
        uint32_t oldRootDepth = 0;
        Node* oldRoot = find(val, &oldRootParent, &oldRootDepth);

        if (!oldRoot)
            return false;

        Node* newRootParent = nullptr;
        uint32_t newRootDepth = oldRootDepth;
        Node* newRoot = findNewRoot(oldRoot, newRootParent, newRootDepth);
        nodeSwap(oldRoot, oldRootParent, newRoot, newRootParent);

        if ((newRootDepth == m_depth || oldRootDepth == m_depth) && (m_depthCounter != 1))
            --m_depthCounter;
        else
            depthUpdate();

        delete oldRoot;
        --m_size;

        return true;
    }

    void depthUpdate()
    {
        m_depth = 0;
        m_depthCounter = 0;

        if (!m_root)
        {
            return;
        }

        Queue<Metadata> order(new Vector<Metadata>(size()));
        order.push({m_root, 1});

        while (order.length() > 0)
        {
            Node* curr = order.front().m_node;
            uint32_t d = order.front().m_val;
            order.pop();

            if (d == m_depth)
                ++m_depthCounter;
            else if (d > m_depth)
            {
                m_depth = d;
                m_depthCounter = 1;
            }

            for (uint32_t i = 0; i < sizeof(curr->m_children)/sizeof(curr->m_children[0]); ++i)
            {
                if (curr->m_children[i])
                    order.push({curr->m_children[i], d + 1});
            }
        }
    }

    Node* m_root;
    uint32_t m_size;
    uint32_t m_depth;
    uint32_t m_depthCounter;

private:
    virtual Node* createNode(const T& value)
    {
        return new Node(value);
    }
};

}