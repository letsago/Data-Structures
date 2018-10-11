#pragma once

#include "stack.h"
#include "vector.h"
#include "queue.h"
#include <string>
#include <algorithm>

namespace pyu
{

template <typename T>
class Tree
{
private:
    struct Node
    {
        Node(const T& value)
        {
            memset(m_children, 0, sizeof(m_children));
            m_value = value;
        }

        T m_value;
        Node* m_children[2];
    };

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
        Node* prev = nullptr;
        Node* curr = find(val, &prev);

        if (curr)
            return false;

        Node* node = createNode(val);

        if (!m_root)
            m_root = node;
        else
            prev->m_children[(prev->m_value < val)] = node;

        ++m_size;
        return true;
    }

    bool remove(const T& val)
    {
        Node* prev = nullptr;
        Node* curr = find(val, &prev);

        if (!curr)
            return false;

        Node* next = curr->m_children[LEFT];

        if (curr != m_root)
            prev->m_children[(prev->m_value < curr->m_value)] = next;
        else
            m_root = next;

        while (next)
        {
            prev = next;
            next = prev->m_children[RIGHT];
        }

        if (curr->m_children[RIGHT])
            prev->m_children[RIGHT] = curr->m_children[RIGHT];

        delete curr;
        --m_size;
        return true;
    }

    uint32_t depth() const
    {
        if (!m_root)
            return 0;

        shared_ptr<LinearStorageInterface<Metadata>> pData(new Vector<Metadata>(size()));
        Queue<Metadata> order(pData);
        order.push({m_root, 1});
        uint32_t d;

        while (order.length() > 0)
        {
            Node* curr = order.front().m_node;
            d = order.front().m_val;
            order.pop();

            for (uint32_t i = 0; i < sizeof(curr->m_children)/sizeof(curr->m_children[0]); ++i)
            {
                if (curr->m_children[i])
                    order.push({curr->m_children[i], d + 1});
            }
        }

        return d;
    }

    friend std::ostream& operator<< (std::ostream& os, const Tree& tree)
    {
        if (tree.m_root)
        {
            Vector<PrintMetadata> printData(tree.size());
            shared_ptr<LinearStorageInterface<uint32_t>> pPrintPos(new Vector<uint32_t>(tree.size()));
            Queue<uint32_t> order(pPrintPos);
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
            shared_ptr<LinearStorageInterface<Node*>> pdata(new Vector<Node*>(size()));
            Stack<Node*> deleteorder(pdata);
            deleteorder.push(m_root);

            while (deleteorder.length() > 0)
            {
                Node* curr = deleteorder.top();
                deleteorder.pop();

                if (curr->m_children[LEFT])
                    deleteorder.push(curr->m_children[LEFT]);

                if (curr->m_children[RIGHT])
                    deleteorder.push(curr->m_children[RIGHT]);

                delete curr;
            }
        }

        m_size = 0;
        m_root = nullptr;
    }

    bool contains(const T& val) const
    {
        return find(val);
    }

    Vector<T> getSorted() const
    {
        Vector<T> sorted(size());
        shared_ptr<LinearStorageInterface<Node*>> nodes(new Vector<Node*>(size()));
        Stack<Node*> stack(nodes);
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
       return false;
    }

protected:
    enum Direction
    {
        LEFT,
        RIGHT
    };

    Node* createNode(const T& value)
    {
        return new Node(value);
    }

private:
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

    Node* find(const T& val, Node** pPrev = nullptr) const
    {
        Node* curr = m_root;

        while (curr && curr->m_value != val)
        {
            if (pPrev)
                *pPrev = curr;

            curr = curr->m_children[(val > curr->m_value)];
        }

        return curr;
    }

    Node* m_root;
    uint32_t m_size;
};

}