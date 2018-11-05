#pragma once

#include "queue.h"
#include "shared_ptr.h"
#include "unorderedmap.h"
#include <algorithm>
#include <functional>
#include <stdexcept>

namespace pyu
{

template <typename T, class HashFunction = std::hash<T>>
class WeightedGraph
{
  public:
    void connect(const T& A, const T& B, const size_t distance)
    {
        if((A == B) && !(contains(A)))
        {
            shared_ptr<GraphNode> node = shared_ptr<GraphNode>(new GraphNode(A));
            m_nodes.insert(A, node);
        }
        else if(A != B)
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

            nodeA->addNeighbor(nodeB, distance);
            nodeB->addNeighbor(nodeA, distance);
        }
    }

    // throws exception if A and B are not connected some way
    uint32_t shortestDistance(const T& A, const T& B) const
    {
        uint32_t minDis = 0;
        bool doesConnectionExist = false;

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

                if(history.at(curr) < (curr->m_neighbors).size())
                {
                    const UnorderedMap<GraphNode*, size_t, PointerHash>& neighbors = curr->m_neighbors;

                    for(Iterator<GraphNode*> it = neighbors.begin(); it != neighbors.end(); ++it)
                    {
                        if((*it) == target)
                        {
                            if(!doesConnectionExist)
                            {
                                minDis = distance + neighbors.at(*it);
                                doesConnectionExist = true;
                            }
                            else
                                minDis = std::min<uint32_t>(minDis, (distance + neighbors.at(*it)));
                        }

                        if(!history.contains(*it))
                        {
                            history.insert(*it, 1);
                            queue.push({*it, distance + neighbors.at(*it)});
                        }
                        else
                            ++history.at(*it);
                    }
                }
            }

            if(doesConnectionExist)
                return minDis;
            else
                throw std::out_of_range("No connection exists");
        }
    }

    bool remove(const T& A)
    {
        if(!contains(A))
            return false;

        GraphNode* target = (m_nodes.at(A)).get();
        const UnorderedMap<GraphNode*, size_t, PointerHash>& targetNeighbors = target->m_neighbors;

        for(Iterator<GraphNode*> it = targetNeighbors.begin(); it != targetNeighbors.end(); ++it)
            (*it)->removeNeighbor(target);

        m_nodes.remove(A);
        return true;
    }

    bool contains(const T& A) const { return m_nodes.contains(A); }

    size_t size() const { return m_nodes.size(); }

    bool empty() const { return (size() == 0); }

    void clear() { m_nodes.clear(); }

  protected:
    struct PointerHash
    {
        uint64_t operator()(const void* key) const { return ((size_t)key) >> 3; }
    };

    struct GraphNode
    {
        GraphNode(const T& value) : m_value(value){};

        bool operator==(const GraphNode& other) const { return m_value == other.m_value; }

        void addNeighbor(GraphNode* neighbor, size_t distance)
        {
            if(!(m_neighbors.contains(neighbor)))
                m_neighbors.insert(neighbor, distance);
            else
                m_neighbors.at(neighbor) = distance;
        }

        void removeNeighbor(GraphNode* neighbor)
        {
            if(m_neighbors.contains(neighbor))
                m_neighbors.remove(neighbor);
        }

        T m_value;
        UnorderedMap<GraphNode*, size_t, PointerHash> m_neighbors;
    };

    struct Metadata
    {
        const GraphNode* m_node;
        size_t m_distance;
    };

    UnorderedMap<T, shared_ptr<GraphNode>, HashFunction> m_nodes;
};

} // namespace pyu
