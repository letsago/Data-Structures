#pragma once

#include "iterator.h"

namespace pyu
{

template <typename T>
class LinearStorageInterface
{
  public:
    T& front() { return at(0); }

    const T& front() const { return at(0); }

    T& back() { return at(length() - 1); }

    const T& back() const { return at(length() - 1); }

    bool insert_back(const T& value) { return insert(length(), value); }

    bool remove_back() { return remove(length() - 1); }

    bool insert_front(const T& value) { return insert(0, value); }

    bool remove_front() { return remove(0); }

    bool empty() const { return (length() == 0); }

    int find(const T& value) const
    {
        uint32_t counter = 0;

        for(Iterator<T> it = begin(); it != end(); ++it)
        {
            if(*it == value)
            {
                return counter;
            }

            ++counter;
        }

        return -1;
    }

    bool contains(const T& value) const
    {
        return (find(value) != -1); // -1 indicates that value was not found
    }

    friend std::ostream& operator<<(std::ostream& os, const LinearStorageInterface& lsi)
    {
        os << "{";
        for(Iterator<T> it = lsi.begin(); it != lsi.end(); ++it)
        {
            os << *it << ",";
        }

        os << "}";
        return os;
    }

    bool operator==(const LinearStorageInterface& other) const
    {
        if(length() != other.length())
        {
            return false;
        }

        Iterator<T> compare = other.begin();
        for(Iterator<T> it = begin(); it != end(); ++it)
        {
            if(*it != *compare)
            {
                return false;
            }

            ++compare;
        }

        return true;
    }

    virtual bool insert(const uint32_t position, const T& value) = 0;
    virtual bool remove(const uint32_t position) = 0;
    virtual T& at(const uint32_t position) = 0;
    virtual const T& at(const uint32_t position) const = 0;
    virtual uint32_t length() const = 0;
    virtual void clear() = 0;
    virtual Iterator<T> begin() = 0;
    virtual Iterator<T> end() = 0;
    virtual const Iterator<T> begin() const = 0;
    virtual const Iterator<T> end() const = 0;
    virtual LinearStorageInterface& operator=(LinearStorageInterface& other) = 0;
    virtual ~LinearStorageInterface(){}; // This enables parent class deconstructor to have priority over child class
                                         // deconstructors
};

} // namespace pyu
