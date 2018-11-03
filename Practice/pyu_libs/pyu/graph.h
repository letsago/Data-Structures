#pragma once

#include "queue.h"
#include "shared_ptr.h"
#include "unorderedmap.h"
#include <functional>
#include <stdexcept>

namespace pyu
{

template <typename T, class HashFunction = std::hash<T>>
class Graph
{
  public:
    void connect(const T& A, const T& B)
    {
        if((A == B) && !(contains(A)))
        {
            shared_ptr<GraphNode> node = shared_ptr<GraphNode>(new GraphNode(A));
            m_nodes.insert(A, node);
        }
        else
        {
            auto createNode = [this](const T& val) {
                shared_ptr<GraphNode> node = shared_ptr<GraphNode>(new GraphNode(val));
                m_nodes.insert(val, node);
            };

            if(!(contains(A)))
                createNode(A);

            if(!(contains(B)))
                createNode(B);

            GraphNode* nodeA = m_nodes.at(A).get();
            GraphNode* nodeB = m_nodes.at(B).get();

            nodeA->addNeighbor(nodeB);
            nodeB->addNeighbor(nodeA);
        }
    }

    // throws exception if A and B are not connected some way
    uint32_t shortestDistance(const T& A, const T& B) const
    {
        if(!(contains(A) && contains(B)))
            throw std::out_of_range("No connection exists");
        else
        {
            const GraphNode* source = (m_nodes.at(A)).get();
            const GraphNode* target = (m_nodes.at(B)).get();

            if(source == target)
                return 0;

            UnorderedMap<const GraphNode*, size_t, PointerHash> history;
            history.insert(source, 0);
            Queue<Metadata> queue(new Vector<Metadata>(size()));
            queue.push({source, 0});

            while(!queue.empty())
            {
                const GraphNode* curr = (queue.front()).m_node;
                const size_t distance = (queue.front()).m_distance;
                queue.pop();

                if(history.at(curr) < (curr->m_neighbors).length())
                {
                    const Vector<GraphNode*>& neighbors = curr->m_neighbors;

                    for(size_t i = 0; i < neighbors.length(); ++i)
                    {
                        if(neighbors.at(i) == target)
                            return (distance + 1);

                        if(!(history.contains(neighbors.at(i))))
                        {
                            history.insert(neighbors.at(i), 1);
                            queue.push({neighbors.at(i), distance + 1});
                        }
                        else
                            ++history.at(neighbors.at(i));
                    }
                }
            }

            throw std::out_of_range("No connection exists");
        }
    }

    bool remove(const T& A)
    {
        if(!contains(A))
            return false;

        GraphNode* target = (m_nodes.at(A)).get();
        const Vector<GraphNode*>& targetNeighbors = target->m_neighbors;

        for(size_t i = 0; i < targetNeighbors.length(); ++i)
            (targetNeighbors.at(i))->removeNeighbor(target);

        m_nodes.remove(A);
        return true;
    }

    bool contains(const T& A) const { return m_nodes.contains(A); }

    size_t size() const { return m_nodes.size(); }

    bool empty() const { return (size() == 0); }

    void clear() { m_nodes.clear(); }

  private:
    struct GraphNode
    {
        GraphNode(const T& value) : m_value(value){};

        bool operator==(const GraphNode& other) const { return m_value == other.m_value; }

        void addNeighbor(GraphNode* neighbor)
        {
            if(!(m_neighbors.contains(neighbor)))
                m_neighbors.insert_back(neighbor);
        }

        void removeNeighbor(GraphNode* neighbor)
        {
            const int pos = m_neighbors.find(neighbor);

            if(pos != -1)
                m_neighbors.remove(pos);
        }

        T m_value;
        Vector<GraphNode*> m_neighbors;
    };

    struct Metadata
    {
        const GraphNode* m_node;
        size_t m_distance;
    };

    struct PointerHash
    {
        uint64_t operator()(const GraphNode* key) const { return ((size_t)key) >> 3; }
    };

    UnorderedMap<T, shared_ptr<GraphNode>, HashFunction> m_nodes;
};

} // namespace pyu
