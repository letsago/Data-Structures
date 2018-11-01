#include <gtest/gtest.h>
#include <pyu/common.h>
#include <pyu/iterator.h>
#include <pyu/orderedset.h>

using namespace pyu;

TEST(OrderedSetTests, PrimitiveTypeInsertTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_FALSE(A.insert(10));
    ASSERT_EQ(A.size(), ARRAYSIZE(arr));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));
}

TEST(OrderedSetTests, PrimitiveTypeRemoveTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};
    Vector<int> data(arr, ARRAYSIZE(arr));

    OrderedSet<int> A;

    ASSERT_FALSE(A.remove(10));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(arr));
    ASSERT_TRUE(A.remove(10));
    ASSERT_FALSE(A.remove(10));
    data.remove(data.find(10));

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());
}

TEST(OrderedSetTests, PrimitiveTypeClearTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    ASSERT_TRUE(A.empty());
    A.clear();
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(arr));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    A.clear();
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_FALSE(A.contains(arr[i]));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(arr));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));
}

TEST(OrderedSetTests, PrimitiveTypeContainsTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    ASSERT_FALSE(A.contains(0));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.contains(arr[i]));

    ASSERT_FALSE(A.contains(-10));
    ASSERT_FALSE(A.contains(0));
}

TEST(OrderedSetTests, PrimitiveTypeComparisonTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};
    const int arr2[] = {10, 20, 8};

    OrderedSet<int> A;
    OrderedSet<int> B;

    ASSERT_TRUE(A == B);

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_FALSE(A == B);

    for(uint32_t i = 0; i < ARRAYSIZE(arr2); ++i)
        ASSERT_TRUE(B.insert(arr2[i]));

    ASSERT_FALSE(A == B);
    B.clear();

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(B.insert(arr[i]));

    ASSERT_TRUE(A == B);
}

TEST(OrderedSetTests, PrimitiveTypeIteratorTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    Tree<int> T;

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(T.insert(arr[i]));

    Vector<int> sorted = T.getSorted();

    OrderedSet<int> A;

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    ASSERT_EQ(A.size(), sorted.length());
    uint32_t index = 0;

    for(Iterator<int> it = A.begin(); it != A.end(); ++it)
    {
        ASSERT_EQ(*it, sorted.at(index));
        ++index;
    }
}

TEST(OrderedSetTests, PrimitiveTypeIteratorFindTest)
{
    const int arr[] = {10, 20, 15, 8, 2, 5};

    OrderedSet<int> A;

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
        ASSERT_TRUE(A.insert(arr[i]));

    for(uint32_t i = 0; i < ARRAYSIZE(arr); ++i)
    {
        Iterator<int> it = A.find(arr[i]);
        ASSERT_EQ(*it, arr[i]);
    }

    Iterator<int> it = A.find(0);
    ASSERT_TRUE(it == A.end());
}

struct ComplexType
{
    ComplexType(uint32_t val) { m_value = val; }

    bool operator>(const ComplexType& other) const { return m_value > other.m_value; }

    bool operator==(const ComplexType& other) const { return m_value == other.m_value; }

    bool operator!=(const ComplexType& other) const { return !(*this == other); }

    uint32_t m_value;
};

TEST(OrderedSetTests, NonPrimitiveInsertTest)
{
    OrderedSet<ComplexType> A;

    ASSERT_TRUE(A.empty());
    ComplexType val(0);
    uint32_t size = 8;

    for(uint32_t i = 0; i < size; ++i)
    {
        val.m_value = i;
        ASSERT_TRUE(A.insert(val));
    }

    for(uint32_t i = 0; i < size; ++i)
    {
        val.m_value = i;
        ASSERT_TRUE(A.contains(val));
    }

    ASSERT_EQ(A.size(), size);
}

TEST(OrderedSetTests, NonPrimitiveRemoveTest)
{
    OrderedSet<ComplexType> A;

    ASSERT_TRUE(A.empty());
    ComplexType val(0);
    ASSERT_FALSE(A.remove(val));
    uint32_t size = 8;

    for(uint32_t i = 0; i < size; ++i)
    {
        val.m_value = i;
        ASSERT_TRUE(A.insert(val));
    }

    for(uint32_t i = 0; i < size; ++i)
    {
        val.m_value = i;
        ASSERT_TRUE(A.contains(val));
    }

    ASSERT_EQ(A.size(), size);
    val.m_value = 0;
    ASSERT_TRUE(A.remove(val));
    ASSERT_FALSE(A.remove(val));
    ASSERT_EQ(A.size(), size - 1);

    for(uint32_t i = 0; i < size - 1; ++i)
    {
        val.m_value = i + 1;
        ASSERT_TRUE(A.contains(val));
    }
}