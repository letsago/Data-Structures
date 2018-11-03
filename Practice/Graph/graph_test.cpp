#include <gtest/gtest.h>
#include <pyu/common.h>
#include <pyu/graph.h>
#include <pyu/vector.h>

using namespace pyu;

template <class T>
class GraphTests : public ::testing::Test
{
};

struct ComplexType
{
    ComplexType(){};

    ComplexType(int val) : m_value(val){};

    bool operator>(const ComplexType& other) const { return m_value > other.m_value; }

    bool operator==(const ComplexType& other) const { return m_value == other.m_value; }

    int m_value;
};

template <typename T>
Vector<T> DataGenerator(const int arr[], size_t size)
{
    return Vector<T>();
}

template <>
Vector<int> DataGenerator<int>(const int arr[], size_t size)
{
    Vector<int> x;

    for(uint32_t i = 0; i < size; ++i)
        x.insert_back(arr[i]);

    return x;
}

template <>
Vector<ComplexType> DataGenerator<ComplexType>(const int arr[], size_t size)
{
    Vector<ComplexType> x;

    for(uint32_t i = 0; i < size; ++i)
    {
        ComplexType value(arr[i]);
        x.insert_back(value);
    }

    return x;
}

typedef testing::Types<int> Implementations;
TYPED_TEST_CASE(GraphTests, Implementations);

TYPED_TEST(GraphTests, DistinctConnectTest)
{
    const int arr[] = {10, 5, 20, 15};
    Vector<TypeParam> data = DataGenerator<TypeParam>(arr, ARRAYSIZE(arr));
    Graph<TypeParam> A;
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.front(), data.at(i));
        ASSERT_EQ(A.size(), i + 1);
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());
}

TYPED_TEST(GraphTests, NonDistinctConnectTest)
{
    const int arr[] = {10, 5, 20, 15};
    Vector<TypeParam> data = DataGenerator<TypeParam>(arr, ARRAYSIZE(arr));
    Graph<TypeParam> A;
    ASSERT_TRUE(A.empty());
    A.connect(data.front(), data.front());
    ASSERT_TRUE(A.contains(data.front()));
    ASSERT_EQ(A.size(), 1);

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.front(), data.at(i));
        ASSERT_EQ(A.size(), i + 1);
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.at(i), data.front());
        ASSERT_EQ(A.size(), data.length());
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());
}

TYPED_TEST(GraphTests, RemoveTest)
{
    const int arr[] = {10, 5, 20, 15};
    Vector<TypeParam> data = DataGenerator<TypeParam>(arr, ARRAYSIZE(arr));
    Graph<TypeParam> A;
    ASSERT_TRUE(A.empty());
    ASSERT_FALSE(A.remove(data.front()));

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.front(), data.at(i));
        ASSERT_EQ(A.size(), i + 1);
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.remove(data.at(i)));
        ASSERT_FALSE(A.remove(data.at(i)));
        ASSERT_EQ(A.size(), data.length() - i - 1);
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_FALSE(A.contains(data.at(i)));

    ASSERT_TRUE(A.empty());
}

TYPED_TEST(GraphTests, ShortestDistanceConnectedTest)
{
    const int arr[] = {10, 5, 20, 15};
    Vector<TypeParam> data = DataGenerator<TypeParam>(arr, ARRAYSIZE(arr));
    Graph<TypeParam> A;
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.front(), data.at(i));
        ASSERT_EQ(A.size(), i + 1);
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());
    ASSERT_EQ(A.shortestDistance(data.front(), data.front()), 0);

    for(uint32_t i = 1; i < data.length(); ++i)
        ASSERT_EQ(A.shortestDistance(data.front(), data.at(i)), 1);

    for(uint32_t i = 2; i < data.length(); ++i)
        ASSERT_EQ(A.shortestDistance(data.at(1), data.at(i)), 2);

    A.connect(data.at(1), data.at(2));
    ASSERT_EQ(A.shortestDistance(data.at(1), data.at(2)), 1);
}

TYPED_TEST(GraphTests, DistinctShortestDistanceNonConnectedTest)
{
    const int arr[] = {10, 5, 20, 15};
    Vector<TypeParam> data = DataGenerator<TypeParam>(arr, ARRAYSIZE(arr));
    Graph<TypeParam> A;
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.front(), data.at(i));
        ASSERT_EQ(A.size(), i + 1);
    }

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 1; i < data.length(); ++i)
        ASSERT_EQ(A.shortestDistance(data.front(), data.at(i)), 1);

    ASSERT_TRUE(A.remove(data.front()));

    for(uint32_t i = 1; i < data.length(); ++i)
        ASSERT_THROW(A.shortestDistance(data.front(), data.at(i)), std::out_of_range);
}

TYPED_TEST(GraphTests, ContainsTest)
{
    const int arr[] = {10, 5, 20, 15};
    Vector<TypeParam> data = DataGenerator<TypeParam>(arr, ARRAYSIZE(arr));
    const int arr2[] = {80};
    Vector<TypeParam> nonContainedData = DataGenerator<TypeParam>(arr2, ARRAYSIZE(arr2));
    Graph<TypeParam> A;
    ASSERT_TRUE(A.empty());

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_FALSE(A.contains(data.at(i)));

    ASSERT_TRUE(A.empty());

    for(uint32_t i = 1; i < data.length(); ++i)
    {
        A.connect(data.front(), data.at(i));
        ASSERT_EQ(A.size(), i + 1);
    }

    for(uint32_t i = 0; i < nonContainedData.length(); ++i)
        ASSERT_FALSE(A.contains(nonContainedData.at(i)));

    for(uint32_t i = 0; i < data.length(); ++i)
        ASSERT_TRUE(A.contains(data.at(i)));

    ASSERT_EQ(A.size(), data.length());
}
