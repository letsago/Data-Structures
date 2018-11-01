#pragma once

#include "linear_storage_interface.h"
#include "shared_ptr.h"

namespace pyu
{

template <typename T>
class Queue
{
  public:
    Queue(shared_ptr<LinearStorageInterface<T>> pLsi) { m_pLsi = pLsi; }

    bool pop() { return m_pLsi->remove_front(); }

    bool push(T value) { return m_pLsi->insert_back(value); }

    T& front() { return m_pLsi->front(); }

    const T& front() const { return m_pLsi->front(); }

    int length() const { return m_pLsi->length(); }

    bool empty() { return m_pLsi->empty(); }

    void clear() { m_pLsi->clear(); }

  private:
    shared_ptr<LinearStorageInterface<T>> m_pLsi;
};

} // namespace pyu