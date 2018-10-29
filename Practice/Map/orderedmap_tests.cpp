#include <gtest/gtest.h>
#include <pyu/orderedmap.h>
#include <pyu/iterator.h>
#include <pyu/common.h>

using namespace pyu;

TEST(OrderedMapTests, IteratorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    Tree<int> T;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(T.insert(keys[i]));

    Vector<int> sorted = T.getSorted();

    OrderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    ASSERT_EQ(A.size(), sorted.length());
    uint32_t index = 0;

    for (Iterator<int> it = A.begin(); it != A.end(); ++it)
    {
        ASSERT_EQ(*it, sorted.at(index));
        ++index;
    }
}