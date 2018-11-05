#pragma once

#include "weightedgraph.h"

namespace pyu
{

template <typename T, class HashFunction = std::hash<T>>
class Graph : public WeightedGraph<T, HashFunction>
{
  public:
    void connect(const T& A, const T& B) { WeightedGraph<T, HashFunction>::connect(A, B, 1); }
};

} // namespace pyu
