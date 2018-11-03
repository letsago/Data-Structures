#include <gtest/gtest.h>
#include <pyu/common.h>
#include <pyu/iterator.h>
#include <pyu/orderedmap.h>
#include <pyu/unorderedmap.h>

using namespace pyu;

template <class T>
class MapPrimitiveTypeTests : public ::testing::Test
{
};

template <class T>
class MapNonPrimitiveValueTests : public ::testing::Test
{
};

template <class T>
class MapNonPrimitiveKeyTests : public ::testing::Test
{
};

struct ComplexType
{
    ComplexType(){};

    ComplexType(uint32_t val) : m_value(val){};

    bool operator>(const ComplexType& other) const { return m_value > other.m_value; }

    bool operator==(const ComplexType& other) const { return m_value == other.m_value; }

    uint32_t m_value;
};

struct IntHash
{
    uint64_t operator()(const int key) const { return static_cast<const uint64_t>(key); }
};

struct ComplexTypeHash
{
    uint64_t operator()(const ComplexType key) const { return static_cast<const uint64_t>(key.m_value); }
};

typedef testing::Types<OrderedMap<int, int>, UnorderedMap<int, int, IntHash>> PrimitiveTypeImplementations;
typedef testing::Types<OrderedMap<int, ComplexType>, UnorderedMap<int, ComplexType, IntHash>>
    NonPrimitiveValueImplementations;
typedef testing::Types<OrderedMap<ComplexType, int>, UnorderedMap<ComplexType, int, ComplexTypeHash>>
    NonPrimitiveKeyImplementations;
TYPED_TEST_CASE(MapPrimitiveTypeTests, PrimitiveTypeImplementations);
TYPED_TEST_CASE(MapNonPrimitiveValueTests, NonPrimitiveValueImplementations);
TYPED_TEST_CASE(MapNonPrimitiveKeyTests, NonPrimitiveKeyImplementations);

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeInsertSuccessTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeInsertFailTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
    {
        ASSERT_TRUE(A.contains(i));
        Iterator<int> it = A.find(i);
        ASSERT_EQ(A.at(*it), values[i]);
    }

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_FALSE(A.insert(i, values[i] * 2));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
    {
        ASSERT_TRUE(A.contains(i));
        Iterator<int> it = A.find(i);
        ASSERT_EQ(A.at(*it), values[i] * 2);
    }
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeRemoveTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};
    Vector<int> data(values, ARRAYSIZE(values));

    TypeParam A;

    ASSERT_FALSE(A.remove(0));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));
    ASSERT_TRUE(A.remove(0));
    ASSERT_FALSE(A.remove(0));
    data.remove(data.find(10));

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(i + 1));

    ASSERT_EQ(A.size(), data.length());
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeClearTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    ASSERT_TRUE(A.empty());
    A.clear();
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    A.clear();
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_FALSE(A.contains(i));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_EQ(A.size(), ARRAYSIZE(values));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeContainsTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    ASSERT_FALSE(A.contains(0));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_FALSE(A.contains(-10));
    ASSERT_FALSE(A.contains(10));
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeComparisonTest)
{
    const int values[] = {10, 20, 15, 8, 2, 5};
    const int values2[] = {10, 20, 8, 2, 15, 5};

    TypeParam A;
    TypeParam B;

    ASSERT_TRUE(A == B);

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(A.insert(i, values[i]));

    ASSERT_FALSE(A == B);

    for(uint32_t i = 0; i < ARRAYSIZE(values2); ++i)
        ASSERT_TRUE(B.insert(i, values2[i]));

    ASSERT_FALSE(A == B);
    B.clear();

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(B.insert(i, values[i]));

    ASSERT_TRUE(A == B);
    B.clear();
    ASSERT_FALSE(A == B);

    const int keys[] = {1, 4, 2, 3, 5, 8};

    for(uint32_t i = 0; i < ARRAYSIZE(values); ++i)
        ASSERT_TRUE(B.insert(keys[i], values[i]));

    ASSERT_FALSE(A == B);
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeIteratorFindTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(*it, keys[i]);
    }

    Iterator<int> it = A.find(0);
    ASSERT_TRUE(it == A.end());
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeAtTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(A.at(*it), i);
    }

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        A.at(*it) = i * 2;
    }

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(A.at(*it), i * 2);
    }
}

TYPED_TEST(MapPrimitiveTypeTests, PrimitiveTypeBracketOperatorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5};

    TypeParam A;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(A[*it], i);
    }

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        A[*it] = i * 2;
    }

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        Iterator<int> it = A.find(keys[i]);
        ASSERT_EQ(A[*it], i * 2);
    }
}

TYPED_TEST(MapNonPrimitiveKeyTests, NonPrimitiveKeyInsertTest)
{
    TypeParam A;

    ASSERT_TRUE(A.empty());
    ComplexType key(0);
    uint32_t size = 8;

    for(uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.insert(key, i));
    }

    for(uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.contains(key));
    }

    ASSERT_EQ(A.size(), size);
}

TYPED_TEST(MapNonPrimitiveKeyTests, NonPrimitiveKeyRemoveTest)
{
    TypeParam A;

    ASSERT_TRUE(A.empty());
    ComplexType key(0);
    ASSERT_FALSE(A.remove(key));
    uint32_t size = 8;

    for(uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.insert(key, i));
    }

    for(uint32_t i = 0; i < size; ++i)
    {
        key.m_value = i;
        ASSERT_TRUE(A.contains(key));
    }

    ASSERT_EQ(A.size(), size);
    key.m_value = 0;
    ASSERT_TRUE(A.remove(key));
    ASSERT_FALSE(A.remove(key));
    ASSERT_EQ(A.size(), size - 1);

    for(uint32_t i = 0; i < size - 1; ++i)
    {
        key.m_value = i + 1;
        ASSERT_TRUE(A.contains(key));
    }
}

TYPED_TEST(MapNonPrimitiveValueTests, NonPrimitiveValueInsertTest)
{
    TypeParam A;

    ASSERT_TRUE(A.empty());
    ComplexType value(0);
    uint32_t size = 8;

    for(uint32_t i = 0; i < size; ++i)
    {
        value.m_value = i;
        ASSERT_TRUE(A.insert(i, value));
    }

    for(uint32_t i = 0; i < size; ++i)
    {
        ASSERT_TRUE(A.contains(i));
        Iterator<int> it = A.find(i);
        ASSERT_EQ(A.at(*it), i);
    }

    ASSERT_EQ(A.size(), size);

    for(uint32_t i = 0; i < size; ++i)
    {
        value.m_value = i * 3;
        ASSERT_FALSE(A.insert(i, value));
    }

    ASSERT_EQ(A.size(), size);

    for(uint32_t i = 0; i < size; ++i)
    {
        ASSERT_TRUE(A.contains(i));
        Iterator<int> it = A.find(i);
        ASSERT_EQ(A.at(*it), i * 3);
    }
}

TYPED_TEST(MapNonPrimitiveValueTests, NonPrimitiveValueRemoveTest)
{
    TypeParam A;

    ASSERT_TRUE(A.empty());
    ComplexType value(0);
    ASSERT_FALSE(A.remove(0));
    uint32_t size = 8;

    for(uint32_t i = 0; i < size; ++i)
    {
        value.m_value = i;
        ASSERT_TRUE(A.insert(i, value));
    }

    for(uint32_t i = 0; i < size; ++i)
        ASSERT_TRUE(A.contains(i));

    ASSERT_EQ(A.size(), size);
    ASSERT_TRUE(A.remove(0));
    ASSERT_FALSE(A.remove(0));
    ASSERT_EQ(A.size(), size - 1);

    for(uint32_t i = 0; i < size - 1; ++i)
        ASSERT_TRUE(A.contains(i + 1));
}
