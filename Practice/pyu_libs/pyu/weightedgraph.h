#pragma once

#include "queue.h"
#include "shared_ptr.h"
#include "unorderedmap.h"
#include <functional>
#include <stdexcept>

namespace pyu
{

template <typename T, class HashFunction = std::hash<T>>
class WeightedGraph
{
  public:
    void connect(const T& A, const T& B, const size_t distance) {}

    // throws exception if A and B are not connected some way
    uint32_t shortestDistance(const T& A, const T& B) const { throw std::out_of_range("No connection exists"); }

    bool remove(const T& A) { return false; }

    bool contains(const T& A) const { return false; }

    size_t size() const { return 0; }

    bool empty() const { return (size() == 0); }

    void clear() {}
};

} // namespace pyu
