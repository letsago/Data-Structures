#pragma once

#include "linear_storage_interface.h"
#include "shared_ptr.h"

namespace pyu
{

template <typename T>
class Stack
{

  public:
    Stack(shared_ptr<LinearStorageInterface<T>> pLsi) { m_pLsi = pLsi; }

    bool pop() { return m_pLsi->remove_back(); }

    bool push(T value) { return m_pLsi->insert_back(value); }

    T& top() { return m_pLsi->back(); }

    const T& top() const { return m_pLsi->back(); }

    int length() const { return m_pLsi->length(); }

    bool empty() { return m_pLsi->empty(); }

    void clear() { m_pLsi->clear(); }

  private:
    shared_ptr<LinearStorageInterface<T>> m_pLsi;
};

} // namespace pyu