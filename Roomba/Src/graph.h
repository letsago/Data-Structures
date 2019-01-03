#pragma once

#include "globals.h"
#include <assert.h>
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>

class Graph
{
  public:
    void connect(const Coordinate& A, const Coordinate& B)
    {
        if((A == B) && !(contains(A)))
        {
            std::shared_ptr<GraphNode> node(new GraphNode(A));
            m_nodes[A] = node;
        }
        else if(A != B)
        {
            auto createNode = [this](const Coordinate& val) {
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

            nodeA->addNeighbor(nodeB);
            nodeB->addNeighbor(nodeA);
        }
    }

    // throws exception if A and B are not connected some way
    uint32_t shortestDistance(const Coordinate& A, const Coordinate& B, const Direction& dir,
                              std::stack<Coordinate>* pPath = nullptr) const
    {
        if(!(contains(A) && contains(B)))
        {
            throw std::out_of_range("A or B nonexistent: No connection exists");
        }

        if(A == B)
        {
            return 0;
        }

        size_t minCost = std::numeric_limits<size_t>::max();
        std::unordered_map<Coordinate, Direction, CoordinateHash> history;

        auto nextSpaceCost = [](const Direction& currDir, const Direction& nextDir) -> size_t {
            return findRotationDiff(nextDir, currDir) + 1;
        };

        auto findExpectedCost = [&B](const Coordinate& currCoor, const Direction& currDir) -> size_t {
            Coordinate movement = B - currCoor;
            size_t rotationCostFirst = 0;
            size_t rotationCostSecond = 0;
            std::pair<Direction, Direction> rightDirs = Coordinate::GetDirectionsfromVector(movement);

            if(currDir != rightDirs.first && rightDirs.first != Direction::NONE)
            {
                rotationCostFirst = findRotationDiff(rightDirs.first, currDir);
            }

            if(currDir != rightDirs.second && rightDirs.second != Direction::NONE)
            {
                rotationCostSecond = findRotationDiff(rightDirs.second, currDir);
            }

            return std::abs(movement.x) + std::abs(movement.y) + rotationCostFirst + rotationCostSecond;
        };

        std::priority_queue<TraversalMetadata, std::vector<TraversalMetadata>> order;
        history[A] = dir;
        order.push({A, 0, findExpectedCost(A, dir), dir});

        while(!order.empty())
        {
            auto curr = order.top();
            order.pop();

            if(curr.coor == B)
            {
                minCost = std::min(minCost, curr.actualCost);
            }

            if(curr.actualCost + curr.expectedCost < minCost)
            {
                const auto& neighbors = m_nodes.at(curr.coor).get()->m_neighbors;

                for(size_t i = 0; i < neighbors.size(); ++i)
                {
                    if(neighbors[i])
                    {
                        const Direction nextDir = static_cast<Direction>(i);
                        const size_t expectedCost = findExpectedCost(neighbors[i]->m_value, nextDir);
                        const size_t actualCost = curr.actualCost + nextSpaceCost(curr.dir, nextDir);

                        if(history.find(neighbors[i]->m_value) == history.end())
                        {
                            history[neighbors[i]->m_value] = nextDir;
                            order.push({neighbors[i]->m_value, actualCost, expectedCost, nextDir});
                        }
                        else
                        {
                            assert(expectedCost + actualCost < minCost);
                        }
                    }
                }
            }
        }

        if(history.find(B) == history.end())
        {
            throw std::out_of_range("No connection exists");
        }

        if(pPath)
        {
            std::stack<Coordinate> shortestPath;
            Coordinate coor = B;

            while(coor != A)
            {
                shortestPath.push(coor);
                const Direction nextDir = static_cast<Direction>((history[coor] + 2) % Direction::COUNT);
                coor = coor + Coordinate::GetCoordinateFromDirection(nextDir);
            }

            *pPath = shortestPath;
        }

        return minCost;
    }

    bool remove(const Coordinate& A)
    {
        if(!contains(A))
        {
            return false;
        }

        std::shared_ptr<GraphNode> target = m_nodes[A];
        const auto& targetNeighbors = target.get()->m_neighbors;

        for(auto neighbor : targetNeighbors)
        {
            if(neighbor)
            {
                neighbor->removeNeighbor(target.get());
            }
        }

        m_nodes.erase(A);
        return true;
    }

    bool contains(const Coordinate& A) const { return m_nodes.find(A) != m_nodes.end(); }

    size_t size() const { return m_nodes.size(); }

    bool empty() const { return (size() == 0); }

    void clear() { m_nodes.clear(); }

  private:
    struct GraphNode
    {
        GraphNode(const Coordinate& value) : m_value(value), m_neighbors({nullptr, nullptr, nullptr, nullptr}){};

        bool operator==(const GraphNode& other) const { return m_value == other.m_value; }

        void addNeighbor(GraphNode* neighbor)
        {
            Direction dir = Coordinate::GetDirectionFromUnitCoordinate(neighbor->m_value - m_value);
            m_neighbors[dir] = neighbor;
        }

        void removeNeighbor(GraphNode* neighbor)
        {
            Direction dir = Coordinate::GetDirectionFromUnitCoordinate(neighbor->m_value - m_value);
            m_neighbors[dir] = nullptr;
        }

        Coordinate m_value;
        std::array<GraphNode*, Direction::COUNT> m_neighbors;
    };

    struct TraversalMetadata
    {
        bool operator<(const TraversalMetadata& other) const
        {
            size_t selfTotalCost = actualCost + expectedCost;
            size_t otherTotalCost = other.actualCost + other.expectedCost;

            if(selfTotalCost == otherTotalCost)
            {
                return expectedCost > other.expectedCost;
            }

            return selfTotalCost > otherTotalCost;
        }

        Coordinate coor;
        size_t actualCost;
        size_t expectedCost;
        Direction dir;
    };

    std::unordered_map<Coordinate, std::shared_ptr<GraphNode>, CoordinateHash> m_nodes;
};
