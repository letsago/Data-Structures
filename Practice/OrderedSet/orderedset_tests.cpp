#include <gtest/gtest.h>
#include <pyu/orderedset.h>
#include <pyu/iterator.h>
#include <pyu/common.h>

using namespace pyu;

TEST(OrderedSetTests, InsertTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_FALSE(A.insert(10));
    ASSERT_EQ(A.size(), ARRAYSIZE(arr));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));
}

TEST(OrderedSetTests, RemoveTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};
    Vector<int> data(arr, ARRAYSIZE(arr));

    OrderedSet<int> A;

    ASSERT_FALSE(A.remove(10));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(arr));
    ASSERT_TRUE(A.remove(10));
    ASSERT_FALSE(A.remove(10));
    data.remove(data.find(10));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(arr));
}

TEST(OrderedSetTests, ClearTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    ASSERT_EQ(A.size(), 0);
    A.clear();
    ASSERT_EQ(A.size(), 0);

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(arr));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    A.clear();
    ASSERT_EQ(A.size(), 0);

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_FALSE(A.contains(arr[i]));
}

TEST(OrderedSetTests, ContainsTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    ASSERT_FALSE(A.contains(0));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    ASSERT_FALSE(A.contains(-10));
    ASSERT_FALSE(A.contains(0));
}

TEST(OrderedSetTests, ComparisonTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};
    const int arr2[] = {10, 20, 8};

    OrderedSet<int> A;
    OrderedSet<int> B;

    ASSERT_TRUE(A == B);

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_FALSE(A == B);

    for (uint32_t i = 0; i < ARRAYSIZE(arr2); ++i)
        ASSERT_TRUE(B.insert(arr2[i]));

    ASSERT_FALSE(A == B);
    B.clear();

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(B.insert(arr[i]));

    ASSERT_TRUE(A == B);
}

TEST(OrderedSetTests, IteratorTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    Tree<int> T;

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(T.insert(arr[i]));

    Vector<int> sorted = T.getSorted();

    OrderedSet<int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_EQ(A.size(), sorted.length());
    uint32_t index = 0;

    for (Iterator<int> it = A.begin(); it != A.end(); ++it)
    {
        ASSERT_EQ(*it, sorted.at(index));
        ++index;
    }
}

TEST(OrderedSetTests, IteratorFindTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    for (uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
    {
        Iterator<int> it = A.find(arr[i]);
        ASSERT_EQ(*it, arr[i]);
    }

    Iterator<int> it = A.find(0);
    ASSERT_TRUE(it == A.end());
}