#pragma once

#include "linear_storage_interface.h"
#include "iterator.h"
#include "shared_ptr.h"

namespace pyu
{

template <typename T, const uint32_t N>
class RollingArray : public LinearStorageInterface<T>
{
    public:
        RollingArray()
        {
            m_size = 0;
            m_head = 0;
            m_data = new T[N];
        }

        RollingArray(const RollingArray& other)
        {
            m_size = 0;
            m_head = 0;
            m_data = nullptr;
            *this = other;
        }

        RollingArray& operator= (LinearStorageInterface<T>& other)
        {
            *this = dynamic_cast<RollingArray&>(other);

            return *this;
        }

        RollingArray& operator= (const RollingArray& other)
        {
            T* new_data = new T[N];
            m_head = other.m_head;
            m_size = other.m_size;
            uint32_t new_index = 0;
            for (uint32_t i = m_head; i < m_size; ++i)
            {
                new_data[new_index] = other.m_data[i];
                ++new_index;
            }

            for (uint32_t i = 0; i < m_head; ++i)
            {
                new_data[new_index] = other.m_data[i];
                ++new_index;
            }

            delete[] m_data;
            m_data = new_data;
            m_head = 0;

            return *this;
        }

        ~RollingArray()
        {
            clear();
            delete[] m_data;
            m_data = nullptr;
        }

        bool insert(const uint32_t position, const T value)
        {
            if (position != m_size)
                return false;

            uint32_t new_size = m_size + 1;

            if (new_size > N)
                return false;

            uint32_t pos = (m_head + m_size) % N;
            m_data[pos] = value;

            m_size = new_size;

            return true;
        }

        bool remove(const uint32_t position)
        {
            if (position != 0)
                return false;

            if (m_size == 0)
                return false;

            --m_size;
            m_head = (m_head + 1) % N;

            return true;
        }

        T& at(const uint32_t position)
        {
            return m_data[m_head];
        }

        const T& at(const uint32_t position) const
        {
            return m_data[m_head];
        }

        T* data()
        {
            return m_data;
        }

        const T* data() const
        {
            return m_data;
        }

        uint32_t length() const
        {
            return m_size;
        }

        void clear()
        {
            m_size = 0;
            m_head = 0;
        }

        Iterator<T> begin() const
        {
            shared_ptr<IteratorNode<T>> node(new RollingArrayIteratorNode(m_data + m_head, const_cast<RollingArray*>(this)));
            return Iterator<T>(node);
        }

        Iterator<T> end() const
        {
            return begin() + m_size;
        }

    private:
        class RollingArrayIteratorNode : public IteratorNode<T>
        {
            public:
                RollingArrayIteratorNode(T* address, RollingArray* rollingarray)
                {
                    m_addr = address;
                    m_src = rollingarray;
                }

                T& value() const
                {
                    return *m_addr;
                }

                RollingArrayIteratorNode& next()
                {
                    ++m_addr;

                    if (m_addr > m_src->m_data + N - 1)
                        m_addr = m_src->m_data;

                    if (m_addr > m_src->m_data + ((m_src->m_size + m_src->m_head) % N) && m_addr < m_src->m_data + m_src->m_head)
                        m_addr = m_src->m_data + ((m_src->m_size + m_src->m_head) % N);

                    return *this;
                }

                bool operator!= (IteratorNode<T>& other) const
                {
                    return m_addr != dynamic_cast<RollingArrayIteratorNode&>(other).m_addr;
                }

            private:
                T* m_addr;
                RollingArray* m_src;
        };

        // Member Variables
        uint32_t m_head;
        uint32_t m_size;
        T* m_data;
};

}