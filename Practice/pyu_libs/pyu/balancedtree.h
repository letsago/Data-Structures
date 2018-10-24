#pragma once

#include "tree.h"

namespace pyu
{

template <typename T>
class BalancedTree : public Tree<T>
{
public:
    BalancedTree() : Tree<T>() {};

    typedef typename Tree<T>::Node Node;
    bool insert(const T& val)
    {
        Node* prev;
        BNode* node = dynamic_cast<BNode*>(Tree<T>::insertNode(val, &prev));

        if (!node)
            return false;

        if (!Tree<T>::isBalanced())
            balance(node, Tree<T>::m_depth);

        return true;
    }

    bool remove(const T& val)
    {
        BNode* targetRoot;

        if (!Tree<T>::removeNode(val, reinterpret_cast<Node**>(&targetRoot)))
            return false;

        while (!isRemoveBalanced(targetRoot))
        {
            balance(findImbalance(targetRoot), Tree<T>::m_depth);
            targetRoot = targetRoot->m_parent;
        }

        if (static_cast<int>(Tree<T>::size()) == (1 << (Tree<T>::depth() - 1)) - 1)
            fullBalance();

        return true;
    }

private:
    typedef typename Tree<T>::Direction Direction;
    struct BNode : Tree<T>::Node
    {
        BNode(const T& value) : Tree<T>::Node(value)
        {
            m_parent = nullptr;
        }

        void reset()
        {
            Tree<T>::Node::reset();
            m_parent = nullptr;
        }

        void connect(Node* conBnode, const Direction dir)
        {
            Tree<T>::Node::m_children[dir] = conBnode;

            if (conBnode)
                dynamic_cast<BNode*>(conBnode)->m_parent = this;
        }

        void replace(Node* bnode, Node* parent)
        {
            if (parent)
                dynamic_cast<BNode*>(parent)->connect(Tree<T>::Node::m_children[Tree<T>::Node::m_value > bnode->m_value], static_cast<Direction>(Tree<T>::Node::m_value > parent->m_value));

            this->reset();

            for (uint32_t i = 0; i < sizeof(Tree<T>::Node::m_children)/sizeof(Tree<T>::Node::m_children[0]); ++i)
            {
                Tree<T>::Node::m_children[i] = bnode->m_children[i];

                if (bnode->m_children[i])
                    dynamic_cast<BNode*>(bnode->m_children[i])->m_parent = this;
            }

            m_parent = dynamic_cast<BNode*>(bnode)->m_parent;
        }

        BNode* getChild(const Direction dir) const
        {
            return dynamic_cast<BNode*>(Tree<T>::Node::m_children[dir]);
        }

        BNode* m_parent;
    };

    BNode* createNode(const T& value)
    {
        return new BNode(value);
    }

    typedef typename Tree<T>::Metadata Metadata;
    bool isFull(BNode* root, BNode* imbal, uint32_t treeDepth, uint32_t rootDepth) const
    {
        Queue<Metadata> queue(new Vector<Metadata>(Tree<T>::size()));
        BNode* rootChild = root->getChild(static_cast<Direction>(root->m_value > imbal->m_value));

        if (!rootChild)
            return false;

        queue.push({rootChild, rootDepth + 1});
        uint32_t d = rootDepth + 1;

        while ((queue.front().m_val + 1) != treeDepth)
        {
            BNode* curr = dynamic_cast<BNode*>(queue.front().m_node);
            d = queue.front().m_val + 1;
            queue.pop();

            for (uint32_t i = 0; i < sizeof(curr->m_children)/sizeof(curr->m_children[0]); ++i)
            {
                if (curr->m_children[i])
                    queue.push({curr->m_children[i], d});
                else
                    return false;
            }
        }

        return true;
    }

    BNode* getTargetChild(const BNode* parent, const Direction dir, uint32_t* pCounter = nullptr) const
    {
        BNode* targetChild = parent->getChild(dir);
        uint32_t dummyCounter = 0;

        while (targetChild && targetChild->getChild(static_cast<Direction>(!dir)))
        {
            targetChild = targetChild->getChild(static_cast<Direction>(!dir));
            ++dummyCounter;
        }

        if (pCounter)
            *pCounter = dummyCounter;

        return targetChild;
    }

    BNode* findImbalance(BNode* targetRoot) const
    {
        if (isRemoveBalanced(targetRoot) && Tree<T>::isBalanced())
            return nullptr;

        BNode* start = targetRoot;
        BNode* imbal = nullptr;
        Queue<Metadata> queue(new Vector<Metadata>(Tree<T>::size() / 2));
        uint32_t treeDepth = Tree<T>::depth();
        uint32_t imbalDepth;

        if (start == Tree<T>::m_root)
            imbalDepth = treeDepth - 1;
        else
            imbalDepth = 2;

        auto setImbal = [&start, &imbal, &queue, &imbalDepth](const Direction dir)
        {
            uint32_t subRootRelDepth = 1;
            queue.push({start->getChild(dir), subRootRelDepth});

            while (queue.front().m_val != imbalDepth && !(queue.empty()))
            {
                BNode* curr = dynamic_cast<BNode*>(queue.front().m_node);
                subRootRelDepth = queue.front().m_val + 1;
                queue.pop();

                if (curr->getChild(static_cast<Direction>(!dir)))
                    queue.push({curr->getChild(static_cast<Direction>(!dir)), subRootRelDepth});

                if (curr->getChild(static_cast<Direction>(dir)))
                    queue.push({curr->getChild(static_cast<Direction>(dir)), subRootRelDepth});
            }

            if (!(queue.empty()))
                imbal = dynamic_cast<BNode*>(queue.front().m_node);
        };

        if (start->getChild(Direction::LEFT))
            setImbal(Direction::LEFT);

        if (!imbal)
            setImbal(Direction::RIGHT);

        return imbal;
    }

    bool isRemoveBalanced(BNode*& targetRoot) const
    {
        while (targetRoot)
        {
            int leftSubTreeDepth = 0;
            int rightSubTreeDepth = 0;

            if (targetRoot->getChild(Direction::LEFT))
                leftSubTreeDepth = static_cast<int>(Tree<T>::findDepth(targetRoot->getChild(Direction::LEFT)));

            if (targetRoot->getChild(Direction::RIGHT))
                rightSubTreeDepth = static_cast<int>(Tree<T>::findDepth(targetRoot->getChild(Direction::RIGHT)));

            if (std::abs(leftSubTreeDepth - rightSubTreeDepth) > 1)
                return false;

            targetRoot = targetRoot->m_parent;
        }

        if (!targetRoot)
            targetRoot = dynamic_cast<BNode*>(Tree<T>::m_root);

        return true;
    }

    void balance(BNode* node, const uint32_t treeDepth)
    {
        if (!node) return;

        Stack<BNode*> stack(new Vector<BNode*>(Tree<T>::size() / 2));
        stack.push(node);

        while (!stack.empty())
        {
            BNode* imbal = stack.top();
            BNode* subRoot = imbal->m_parent->m_parent;
            bool doesSubRootChange = false;
            uint32_t subRootDepth = treeDepth - 2;
            uint32_t imbalDepth = treeDepth;
            while (isFull(subRoot, imbal, treeDepth, subRootDepth))
            {
                subRoot = subRoot->m_parent;
                doesSubRootChange = true;
                --subRootDepth;
            }

            BNode* newRoot = getTargetChild(subRoot, static_cast<Direction>(imbal->m_value > subRoot->m_value));

            if (newRoot->m_value == imbal->m_value)
                imbalDepth = subRootDepth;

            if (newRoot->getChild(static_cast<Direction>(newRoot->m_parent->m_value > newRoot->m_value)))
                --imbalDepth;

            ++subRootDepth;
            Tree<T>::nodeSwap(subRoot, subRoot->m_parent, newRoot, newRoot->m_parent);

            Direction targetDir = static_cast<Direction>(subRoot->m_value > newRoot->m_value);

            if (newRoot->getChild(targetDir))
            {
                ++subRootDepth;
                uint32_t counter = 0;
                BNode* rootNewParent = getTargetChild(newRoot, static_cast<Direction>(targetDir), &counter);
                subRootDepth += counter;
                rootNewParent->connect(subRoot, static_cast<Direction>(subRoot->m_value > rootNewParent->m_value));
            }
            else
                newRoot->connect(subRoot, static_cast<Direction>(subRoot->m_value > newRoot->m_value));

            if (!doesSubRootChange || imbalDepth != treeDepth)
                stack.pop();

            if (subRootDepth == treeDepth)
                stack.push(subRoot);
        }

        if (Tree<T>::m_depthCounter == 1)
            Tree<T>::depthUpdate();
        else
            --Tree<T>::m_depthCounter;
    }

    Vector<BNode*> getSortedBNodes() const
    {
        Vector<BNode*> sortedBNodes(Tree<T>::size());
        Stack<BNode*> stack(new Vector<BNode*>(Tree<T>::size()));
        BNode* curr = dynamic_cast<BNode*>(Tree<T>::m_root);

        while (!stack.empty() || curr)
        {
            while (curr)
            {
                stack.push(curr);
                curr = curr->getChild(Direction::LEFT);
            }

            curr = stack.top();
            stack.pop();
            sortedBNodes.insert_back(curr);
            curr = curr->getChild(Direction::RIGHT);
        }

        return sortedBNodes;
    }

    void fullBalance()
    {
        Vector<BNode*> sortedBNodes = getSortedBNodes();
        Vector<uint32_t> relationCounters(Tree<T>::size() / 2);
        uint32_t index = 0;
        uint32_t relationCounter = 1;

        for (uint32_t i = 0; i < Tree<T>::size(); ++i)
        {
            sortedBNodes.at(i)->reset();

            if (i % 2 == 1)
            {
                if ((i - 1) / 2 == relationCounter - 1)
                {
                    relationCounters.insert_back(relationCounter);
                    relationCounter *= 2;
                    index = 0;
                }
                else
                {
                    uint32_t prevRelationCounter = relationCounters.at(index);
                    relationCounters.insert_back(prevRelationCounter);
                    ++index;
                }

                (sortedBNodes.at(i))->connect(sortedBNodes.at(i - relationCounters.back()), Direction::LEFT);
                (sortedBNodes.at(i))->connect(sortedBNodes.at(i + relationCounters.back()), Direction::RIGHT);
            }
        }

        Tree<T>::m_root = sortedBNodes.at(Tree<T>::size() / 2);
        --Tree<T>::m_depth;
        Tree<T>::m_depthCounter = 1 << (Tree<T>::m_depth - 1);
    }
};

}