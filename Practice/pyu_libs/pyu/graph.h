#pragma once

#include <stdexcept>

namespace pyu
{
template <typename T>
class Graph
{
  public:
    void connect(const T& A, const T& B) {}

    // throws exception if A and B are not connected some way
    uint32_t shortestDistance(const T& A, const T& B) const { throw std::out_of_range("No connection exists"); }

    bool remove(const T& A) { return false; }

    bool contains(const T& A) const { return false; }

    size_t size() const { return m_size; }

    bool empty() const { return (size() == 0); }

  private:
    size_t m_size;
};

} // namespace pyu