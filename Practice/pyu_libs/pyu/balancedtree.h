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
        uint32_t depth;
        BNode* node = dynamic_cast<BNode*>(Tree<T>::insertNode(val, &prev, &depth));

        if (!node)
            return false;

        node->m_parent = dynamic_cast<BNode*>(prev);
        balance(node, depth);
        return true;
    }

    bool remove(const T& val)
    {
        return true;
    }

private:
    struct BNode : Tree<T>::Node
    {
        BNode(const T& value) : Tree<T>::Node(value)
        {
            m_parent = nullptr;
        }

        BNode* m_parent;
    };

    BNode* createNode(const T& value)
    {
        return new BNode(value);
    }

    void nodeSwitch(BNode* root, BNode* target, uint32_t& rootDepth, uint32_t& imbalDepth)
    {
        ++rootDepth;

        if (target->m_parent == root)
        {
            target->m_children[root->m_value > target->m_value] = root;
            target->m_parent = root->m_parent;
            memset(root->m_children, 0, sizeof(root->m_children));

            if (root->m_parent)
                root->m_parent->m_children[root->m_value > root->m_parent->m_value] = target;

            root->m_parent = target;
        }
        else
        {
            target->m_parent->m_children[(target->m_value > target->m_parent->m_value)] = target->m_children[!(target->m_value > target->m_parent->m_value)];

            if (target->m_children[!(target->m_value > target->m_parent->m_value)])
            {
                dynamic_cast<BNode*>(target->m_children[!(target->m_value > target->m_parent->m_value)])->m_parent = target->m_parent;
                --imbalDepth;
            }

            target->m_parent = root->m_parent;

            if (root->m_parent)
                root->m_parent->m_children[target->m_value > root->m_parent->m_value] = target;

            for (uint32_t i = 0; i < sizeof(target->m_children)/sizeof(target->m_children[0]); ++i)
            {
                target->m_children[i] = root->m_children[i];

                if (root->m_children[i])
                    dynamic_cast<BNode*>(root->m_children[i])->m_parent = target;
            }

            if (root->m_children[(root->m_value > target->m_value)])
            {
                ++rootDepth;
                BNode* rootParent = dynamic_cast<BNode*>(root->m_children[(root->m_value > target->m_value)]);

                while (rootParent->m_children[!(root->m_value > target->m_value)])
                {
                    ++rootDepth;
                    rootParent = dynamic_cast<BNode*>(rootParent->m_children[!(root->m_value > target->m_value)]);
                }

                root->m_parent = rootParent;
                rootParent->m_children[!(root->m_value > target->m_value)] = root;
            }
            else
            {
                root->m_parent = target;
                target->m_children[(root->m_value > target->m_value)] = root;
            }

            memset(root->m_children, 0, sizeof(root->m_children));
        }

        if (root == Tree<T>::m_root)
            Tree<T>::m_root = target;
    }

    typedef typename Tree<T>::Metadata Metadata;
    bool isFull(BNode* root, BNode* imbal, uint32_t treeDepth, uint32_t rootDepth)
    {
        shared_ptr<LinearStorageInterface<Metadata>> pNodes(new Vector<Metadata>(Tree<T>::size()));
        Queue<Metadata> queue(pNodes);
        BNode* rootChild;
        rootChild = dynamic_cast<BNode*>(root->m_children[root->m_value > imbal->m_value]);

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

    void balance(BNode* node, uint32_t treeDepth)
    {
        if (!Tree<T>::isBalanced(treeDepth))
        {
            shared_ptr<LinearStorageInterface<BNode*>> pData(new Vector<BNode*>(Tree<T>::size() / 2));
            Queue<BNode*> queue(pData);
            queue.push(node);

            while (!queue.empty())
            {
                BNode* imbal = queue.front();
                BNode* root = imbal->m_parent->m_parent;
                bool enter = false;
                uint32_t rootDepth = treeDepth - 2;
                uint32_t imbalDepth = treeDepth;
                while (isFull(root, imbal, treeDepth, rootDepth))
                {
                    root = root->m_parent;
                    enter = true;
                    --rootDepth;
                }

                BNode* target;
                target = dynamic_cast<BNode*>(root->m_children[(imbal->m_value > root->m_value)]);

                while (target->m_children[!(imbal->m_value > root->m_value)])
                    target = dynamic_cast<BNode*>(target->m_children[!(imbal->m_value > root->m_value)]);

                if (target->m_value == imbal->m_value)
                    imbalDepth = rootDepth;

                nodeSwitch(root, target, rootDepth, imbalDepth);

                if (rootDepth == treeDepth)
                    queue.push(root);

                if (!enter || imbalDepth != treeDepth)
                    queue.pop();
            }
        }
    }
};

}