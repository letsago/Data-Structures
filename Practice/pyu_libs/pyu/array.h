#pragma once

#include "linear_storage_interface.h"
#include "iterator.h"
#include "shared_ptr.h"

namespace pyu
{

template <typename T, const uint32_t N>
class Array : public LinearStorageInterface<T>
{
    public:
        Array()
        {
            m_size = 0;
            m_data = new T[N];
        }

        Array(const Array& other)
        {
            m_data = new T[N];
            *this = other;
        }

        Array& operator= (LinearStorageInterface<T>& other)
        {
            *this = dynamic_cast<Array&>(other);

            return *this;
        }

        Array& operator= (const Array& other)
        {
            for (uint32_t i = 0; i < other.m_size; ++i)
                m_data[i] = other.m_data[i];

            m_size = other.m_size;

            return *this;
        }

        ~Array()
        {
            clear();
            delete[] m_data;
            m_data = nullptr;
        }

        bool insert(const uint32_t position, const T& value)
        {
            // cannot insert past actual size of array
            if (position > m_size)
                return false;

            uint32_t new_size = m_size + 1;

            if (new_size > N)
                return false;

            for (uint32_t i = new_size - 1; i > position; i--)
                m_data[i] = m_data[i - 1];

            m_data[position] = value;
            m_size = new_size;

            return true;
        }

        bool remove(const uint32_t position)
        {
            if (position >= m_size)
                return false;   // remove fails if position exceeds actual size of Array

            --m_size;

            for (uint32_t i = position; i < m_size; i++)
                m_data[i] = m_data[i + 1];

            return true;
        }

        T& at(const uint32_t position)
        {
            return m_data[position];
        }

        const T& at(const uint32_t position) const
        {
            return m_data[position];
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

        uint32_t capacity() const
        {
            return N;
        }

        void clear()
        {
            m_size = 0;
        }

        Iterator<T> begin()
        {
            shared_ptr<IteratorNode<T>> node(new ArrayIteratorNode(m_data, this));
            return Iterator<T>(node);
        }

        Iterator<T> end()
        {
            shared_ptr<IteratorNode<T>> node(new ArrayIteratorNode(m_data + length(), this));
            return Iterator<T>(node);
        }

        const Iterator<T> begin() const
        {
            shared_ptr<IteratorNode<T>> node(new ArrayIteratorNode(m_data, this));
            return Iterator<T>(node);
        }

        const Iterator<T> end() const
        {
            shared_ptr<IteratorNode<T>> node(new ArrayIteratorNode(m_data + length(), this));
            return Iterator<T>(node);
        }

    private:
        class ArrayIteratorNode : public IteratorNode<T>
        {
        public:
            ArrayIteratorNode(T* address, const Array* array)
            {
                m_addr = address;
                m_src = array;
            }

            T& value()
            {
                return *m_addr;
            }

            const T& value() const
            {
                return *m_addr;
            }

            ArrayIteratorNode& next()
            {
                ++m_addr;

                if (m_addr > m_src->m_data + m_src->m_size)
                    m_addr = m_src->m_data + m_src->m_size;

                return *this;
            }

            bool operator!= (const IteratorNode<T>& other) const
            {
                return m_addr != dynamic_cast<const ArrayIteratorNode&>(other).m_addr;
            }

        private:
            T* m_addr;
            const Array* m_src;
        };

        // Member Variables
        uint32_t m_size;
        T* m_data;
};

}
