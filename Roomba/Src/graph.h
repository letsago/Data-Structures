#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <queue>
#include <stdexcept>
#include <unordered_map>

template <typename T, class HashFunction = std::hash<T>>
class Graph
{
  public:
    void connect(const T& A, const T& B, const size_t distance)
    {
        if((A == B) && !(contains(A)))
        {
            std::shared_ptr<GraphNode> node(new GraphNode(A));
            m_nodes[A] = node;
        }
        else if(A != B)
        {
            auto createNode = [this](const T& val) {
                std::shared_ptr<GraphNode> node(new GraphNode(val));
                m_nodes[val] = node;
            };

            if(!(contains(A)))
            {
                createNode(A);
            }

            if(!(contains(B)))
            {
                createNode(B);
            }

            GraphNode* nodeA = m_nodes[A].get();
            GraphNode* nodeB = m_nodes[B].get();

            nodeA->addNeighbor(nodeB, distance);
            nodeB->addNeighbor(nodeA, distance);
        }
    }

    // throws exception if A and B are not connected some way
    uint32_t shortestDistance(const T& A, const T& B, std::queue<T>* pPath = nullptr) const
    {
        uint32_t minDis = 0;
        std::queue<T> shortestPath;
        bool doesConnectionExist = false;

        if(!(contains(A) && contains(B)))
        {
            throw std::out_of_range("No connection exists");
        }

        const GraphNode* source = m_nodes.at(A).get();
        const GraphNode* target = m_nodes.at(B).get();

        if(source == target)
        {
            return 0;
        }

        std::unordered_map<const GraphNode*, size_t> history;
        history[source] = 0;
        std::queue<Metadata> queue;
        queue.push({source, 0, shortestPath});

        while(!queue.empty())
        {
            const GraphNode* curr = (queue.front()).m_node;
            const size_t distance = (queue.front()).m_distance;
            std::queue<T> path = (queue.front()).m_path;
            queue.pop();

            if(history.at(curr) < (curr->m_neighbors).size())
            {
                const std::unordered_map<GraphNode*, size_t>& neighbors = curr->m_neighbors;

                for(auto it = neighbors.begin(); it != neighbors.end(); ++it)
                {
                    if(it->first == target)
                    {
                        if(!doesConnectionExist)
                        {
                            minDis = distance + neighbors.at(it->first);
                            shortestPath = path;
                            shortestPath.push(it->first->m_value);
                            doesConnectionExist = true;
                        }
                        else
                        {
                            uint32_t oldMinDis = minDis;
                            minDis = std::min<uint32_t>(minDis, (distance + neighbors.at(it->first)));

                            if(oldMinDis != minDis)
                            {
                                shortestPath = path;
                                shortestPath.push(it->first->m_value);
                            }
                        }
                    }

                    if(history.find(it->first) == history.end())
                    {
                        std::queue<T> tempPath = path;
                        tempPath.push(it->first->m_value);
                        history[it->first] = 1;
                        queue.push({it->first, distance + neighbors.at(it->first), tempPath});
                    }
                    else
                    {
                        ++history.at(it->first);
                    }
                }
            }
        }

        if(pPath)
        {
            *pPath = shortestPath;
        }

        if(doesConnectionExist)
        {
            return minDis;
        }
        throw std::out_of_range("No connection exists");
    }

    bool remove(const T& A)
    {
        if(!contains(A))
        {
            return false;
        }

        GraphNode* target = m_nodes[A];
        const std::unordered_map<GraphNode*, size_t>& targetNeighbors = target->m_neighbors;

        for(auto it = targetNeighbors.begin(); it != targetNeighbors.end(); ++it)
        {
            (it->first)->removeNeighbor(target);
        }

        m_nodes.erase(A);
        return true;
    }

    bool contains(const T& A) const { return m_nodes.find(A) != m_nodes.end(); }

    size_t size() const { return m_nodes.size(); }

    bool empty() const { return (size() == 0); }

    void clear() { m_nodes.clear(); }

  private:
    struct GraphNode
    {
        GraphNode(const T& value) : m_value(value){};

        bool operator==(const GraphNode& other) const { return m_value == other.m_value; }

        void addNeighbor(GraphNode* neighbor, size_t distance) { m_neighbors[neighbor] = distance; }

        void removeNeighbor(GraphNode* neighbor)
        {
            if(m_neighbors.find(neighbor) != m_neighbors.end())
            {
                m_neighbors.erase(neighbor);
            }
        }

        T m_value;
        std::unordered_map<GraphNode*, size_t> m_neighbors;
    };

    struct Metadata
    {
        const GraphNode* m_node;
        size_t m_distance;
        std::queue<T> m_path;
    };

    std::unordered_map<T, std::shared_ptr<GraphNode>, HashFunction> m_nodes;
};
