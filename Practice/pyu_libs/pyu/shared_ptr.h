#pragma once

namespace pyu
{

template <typename T>
class shared_ptr
{
    public:

        shared_ptr(T* p)
        {
            m_pdata = p;
            m_counter = new int(1);
        }

        ~shared_ptr()
        {
            clear();
        }

        shared_ptr(const shared_ptr& p)
        {
            *this = p;
        }

        T& operator* () const
        {
            return *get();
        }

        T* operator-> () const
        {
            return get();
        }

        T* get() const
        {
            return m_pdata;
        }

        shared_ptr<T>& operator= (const shared_ptr<T>& other)
        {
            if (m_pdata != other.m_pdata)
            {
                if (m_pdata != nullptr)
                    clear();

                m_pdata = other.m_pdata;
                m_counter = other.m_counter;
                (*m_counter)++;
            }

            return *this;
        }

        void clear()
        {
            if (m_counter != nullptr)
            {
                if (*m_counter == 1)
                {
                    delete m_pdata;
                    delete m_counter;
                }
                else
                {
                    (*m_counter)--;
                }
            }

            m_counter = nullptr;
            m_pdata = nullptr;
        }

        void reset(T* p)
        {
            clear();
            m_pdata = p;
            m_counter = new int(1);
        }

    private:

        T* m_pdata = nullptr;
        int* m_counter = nullptr;

};

}