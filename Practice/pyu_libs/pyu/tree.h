#pragma once

#include "stack.h"
#include "vector.h"
#include "queue.h"
#include <string>
#include <cmath>
#include <algorithm>

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
        if (tree.m_root != nullptr)
        {
            Vector<PrintMetadata> printData(tree.size());
            shared_ptr<LinearStorageInterface<uint32_t>> pPrintPos(new Vector<uint32_t>(tree.size()));
            Queue<uint32_t> order(pPrintPos);
            printData.insert_back({tree.m_root, std::to_string(tree.m_root->m_value), 1, 0});
            order.push(printData.length() - 1);
            uint32_t numSpaces = 3;
            double minRelCol = 0;
            double maxRelCol = 0;

            auto addNode = [&printData, &order, &numSpaces](const PrintMetadata& obj, Node* next, double colDelta) {
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

                if (obj.m_node->m_right)
                {
                    addNode(obj, obj.m_node->m_right, relColDiff);
                }

                if (obj.m_node->m_left)
                {
                    addNode(obj, obj.m_node->m_left, -relColDiff);
                }
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

                if (printData.at(i).m_node->m_left || printData.at(i).m_node->m_right)
                {
                    uint32_t arrowPos = (numSpaces * (maxCol + 1) + 1) + (printData.at(i).m_relCol * normFactor + transFactor) * numSpaces + numSpaces / 2;
                    output.replace(arrowPos, 1, "|");

                    int numLines = lineCounter * numSpaces + numSpaces / 2 - 1;

                    std::string lines;
                    for (int i = 0; i < numLines; ++i)
                        lines += "_";

                    const uint32_t position = (numSpaces * (maxCol + 1) + 1) + arrowPos;

                    if (printData.at(i).m_node->m_left)
                    {
                        output.replace(arrowPos - numLines, numLines, lines);
                        output.replace(position - numLines - 1, 1, "/");
                    }

                    if (printData.at(i).m_node->m_right)
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

    Vector<T> getSorted() const
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

    bool isBalanced() const
    {
       return false;
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