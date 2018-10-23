#include <gtest/gtest.h>
#include <pyu/orderedmap.h>
#include <pyu/iterator.h>
#include <pyu/common.h>

using namespace pyu;

TEST(OrderedMapTests, PrimitiveTypeInsertTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    OrderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_FALSE(A.insert(0, 10));
    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));
}

TEST(OrderedMapTests, PrimitiveTypeRemoveTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};
    Vector<int> data(values, ARRAYSIZE(values));

    OrderedMap<int, int> A;

    ASSERT_FALSE(A.remove(0));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));
    ASSERT_TRUE(A.remove(0));
    ASSERT_FALSE(A.remove(0));
    data.remove(data.find(10));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));
}

TEST(OrderedMapTests, PrimitiveTypeClearTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    OrderedMap<int, int> A;

    ASSERT_TRUE(A.empty());
    A.clear();
    ASSERT_TRUE(A.empty());

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    A.clear();
    ASSERT_TRUE(A.empty());

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_FALSE(A.contains(i));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));
}

TEST(OrderedMapTests, PrimitiveTypeContainsTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    OrderedMap<int, int> A;

    ASSERT_FALSE(A.contains(0));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_FALSE(A.contains(-10));
    ASSERT_FALSE(A.contains(10));
}

TEST(OrderedMapTests, PrimitiveTypeComparisonTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};
    const int values2[] = {10, 20, 8};

    OrderedMap<int, int> A;
    OrderedMap<int, int> B;

    ASSERT_TRUE(A == B);

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_FALSE(A == B);

    for (uint32_t i = 0; i < ARRAYSIZE(values2); ++i)
        ASSERT_TRUE(B.insert(i, values2[i]));

    ASSERT_FALSE(A == B);
    B.clear();

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(B.insert(i, values[i]));

    ASSERT_TRUE(A == B);
    B.clear();
    ASSERT_FALSE(A == B);

    const int keys[] = {1, 1, 2, 3, 5, 8};

    for (uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(B.insert(keys[i], values[i]));

    ASSERT_TRUE(A == B);
}

TEST(OrderedMapTests, PrimitiveTypeIteratorTest)
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

TEST(OrderedMapTests, PrimitiveTypeIteratorFindTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    OrderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(*it, keys[i]);
    }

    Iterator<int> it = A.find(0);
    ASSERT_TRUE(it == A.end());
}

TEST(OrderedMapTests, PrimitiveTypeAtTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    OrderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(A.at(*it), i);
    }
}

TEST(OrderedMapTests, PrimitiveTypeBracketOperatorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    OrderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(A[*it], i);
    }
}

struct ComplexType
{
    ComplexType(uint32_t val)
    {
        m_value = val;
    }

    bool operator> (const ComplexType& other)
    {
        return m_value > other.m_value;
    }

    bool operator== (const ComplexType& other)
    {
        return m_value == other.m_value;
    }

    uint32_t m_value;
};

TEST(OrderedMapTests, NonPrimitiveKeyInsertTest)
{
    OrderedMap<ComplexType, uint32_t> A;

    ASSERT_TRUE(A.empty());
    ComplexType key(0);
    uint32_t size = 8;

    for (uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.insert(key, i));
    }

    for (uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.contains(key));
    }

    ASSERT_EQ(A.size(), size);
}

TEST(OrderedMapTests, NonPrimitiveKeyRemoveTest)
{
    OrderedMap<ComplexType, uint32_t> A;

    ASSERT_TRUE(A.empty());
    ComplexType key(0);
    ASSERT_FALSE(A.remove(key));
    uint32_t size = 8;

    for (uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.insert(key, i));
    }

    for (uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.contains(key));
    }

    ASSERT_EQ(A.size(), size);
    key.m_value = 0;
    ASSERT_TRUE(A.remove(key));
    ASSERT_FALSE(A.remove(key));
    ASSERT_EQ(A.size(), size - 1);

    for (uint32_t i = 0; i < size - 1; ++i)
    {
        key.m_value = i + 1;
        ASSERT_TRUE(A.contains(key));
    }
}

TEST(OrderedMapTests, NonPrimitiveValueInsertTest)
{
    OrderedMap<uint32_t, ComplexType> A;

    ASSERT_TRUE(A.empty());
    ComplexType key(0);
    uint32_t size = 8;

    for (uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.insert(i, key));
    }

    for (uint32_t i = 0; i < size; ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_EQ(A.size(), size);
}

TEST(OrderedMapTests, NonPrimitiveValueRemoveTest)
{
    OrderedMap<uint32_t, ComplexType> A;

    ASSERT_TRUE(A.empty());
    ComplexType key(0);
    ASSERT_FALSE(A.remove(0));
    uint32_t size = 8;

    for (uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.insert(i, key));
    }

    for (uint32_t i = 0; i < size; ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_EQ(A.size(), size);
    ASSERT_TRUE(A.remove(0));
    ASSERT_FALSE(A.remove(0));
    ASSERT_EQ(A.size(), size - 1);

    for (uint32_t i = 0; i < size - 1; ++i)
        ASSERT_TRUE(A.contains(i + 1));
}