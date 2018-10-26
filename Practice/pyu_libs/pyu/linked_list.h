#pragma once

#include "linear_storage_interface.h"
#include "vector.h"
#include "iterator.h"
#include "shared_ptr.h"

namespace pyu
{

template <typename T>
class LinkedList : public LinearStorageInterface<T>
{
    private:
        struct LLNode
        {
            LLNode(T value, LLNode* next)
            {
                m_value = value;
                m_next = next;
            }

            T m_value;
            LLNode* m_next;
        };

    public:
        LinkedList()
        {
            m_head = nullptr;
            m_size = 0;
        }

        ~LinkedList()
        {
            clear();
        }

        LinkedList(const LinkedList& other)
        {
            m_head = nullptr;
            m_size = 0;
            *this = other;
        }

        LinkedList& operator= (LinearStorageInterface<T>& other)
        {
            *this = dynamic_cast<LinkedList&>(other);

            return *this;
        }

        LinkedList& operator= (const LinkedList& other)
        {
            clear();

            for (Iterator<T> it = other.begin(); it != other.end(); ++it)
                LinearStorageInterface<T>::insert_back(*it);

            return *this;
        }

        uint32_t length() const
        {
            return m_size;
        }

        bool insert(const uint32_t position, const T& value)
        {
            if (position > m_size)
                return false;

            LLNode* next = m_head;
            LLNode* prev = nullptr;

            for (uint32_t i = 1; i <= position; ++i)
            {
                prev = next;
                next = prev -> m_next;
            }

            LLNode* newNode = new LLNode(value, next);

            if (next == m_head)
            {
                m_head = newNode;
            }
            else
            {
                prev -> m_next = newNode;
            }

            ++m_size;

            return true;
        }

        bool remove(const uint32_t position)
        {
            if (m_head == nullptr)
                return false;

            if (position > m_size - 1)
                return false;

            LLNode* deleted = m_head;
            LLNode* prev = nullptr;

            for (uint32_t i = 0; i < position; ++i)
            {
                prev = deleted;
                deleted = prev -> m_next;
            }

            if (deleted == m_head)
            {
                m_head = m_head -> m_next;
            }
            else
            {
                prev -> m_next = deleted -> m_next;
            }

            delete deleted;
            --m_size;

            return true;
        }

        T& at(const uint32_t position)
        {
            LLNode* current = m_head;

            for (uint32_t i = 0; i < position; ++i)
            {
                current = current -> m_next;
            }

            T& value = current -> m_value;

            return value;
        }

        const T& at(const uint32_t position) const
        {
            LLNode* current = m_head;

            for (uint32_t i = 0; i < position; ++i)
            {
                current = current -> m_next;
            }

            T& value = current -> m_value;

            return value;
        }

        Vector<int> findmany(const T value) const
        {
            Vector<int> indices;
            uint32_t counter = 0;

            for (Iterator<T> it = begin(); it != end(); ++it)
            {
                if (*it == value)
                    indices.insert_back(counter);

                ++counter;
            }

            return indices;
        }

        void clear()
        {
            LLNode* curr = m_head;
            LLNode* next;

            while (curr != nullptr)
            {
                next = curr -> m_next;
                delete curr;
                curr = next;
            }

            m_head = nullptr;
            m_size = 0;
        }

        Iterator<T> begin() const
        {
            shared_ptr<IteratorNode<T>> node(new LLIteratorNode(m_head));
            return Iterator<T>(node);
        }

        Iterator<T> end() const
        {
            shared_ptr<IteratorNode<T>> node(new LLIteratorNode(nullptr));
            return Iterator<T>(node);
        }

    private:
        class LLIteratorNode : public IteratorNode<T>
        {
            public:
                LLIteratorNode(LLNode* node)
                {
                    m_curr = node;
                }

                T& value() const
                {
                    return m_curr->m_value;
                }

                LLIteratorNode& next()
                {
                    if (m_curr != nullptr)
                        m_curr = m_curr->m_next;

                    return *this;
                }

                bool operator!= (const IteratorNode<T>& other) const
                {
                    return m_curr != dynamic_cast<const LLIteratorNode&>(other).m_curr;
                }

            private:
                LLNode* m_curr;
        };

        uint32_t m_size;
        LLNode* m_head;

};

}