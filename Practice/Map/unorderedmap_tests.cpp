#include <functional>
#include <gtest/gtest.h>
#include <pyu/common.h>
#include <pyu/iterator.h>
#include <pyu/orderedset.h>
#include <pyu/unorderedmap.h>
#include <pyu/vector.h>
#include <stdexcept>
#include <type_traits>

using namespace pyu;

template <class T>
class HashTests : public ::testing::Test
{
};

struct IntHash
{
    uint64_t operator()(const int key) const { return static_cast<const uint64_t>(key); }
};

struct IntHash2
{
    uint64_t operator()(const int key) const { return (static_cast<const uint64_t>(key) * 2); }
};

template <typename T>
Vector<int> OrderGenerator()
{
    const int data[] = {8, 20, 1, 5, 18, 10, 2, 23, 31, 15};
    Vector<int> order(data, ARRAYSIZE(data));
    return order;
}

template <>
Vector<int> OrderGenerator<IntHash2>()
{
    const int data[] = {20, 8, 1, 5, 18, 10, 2, 23, 31, 15};
    Vector<int> order(data, ARRAYSIZE(data));
    return order;
}

typedef testing::Types<IntHash, IntHash2, std::hash<int>> Implementations;
TYPED_TEST_CASE(HashTests, Implementations);

TYPED_TEST(HashTests, GeneralMapIteratorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int, TypeParam> A;
    OrderedSet<int> B;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
        ASSERT_TRUE(B.insert(keys[i]));
    }

    ASSERT_EQ(A.size(), B.size());

    for(Iterator<int> it = A.begin(); it != A.end(); ++it)
    {
        ASSERT_TRUE(B.remove(*it));
    }
}

TYPED_TEST(HashTests, OutofRangeBucketIteratorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int, TypeParam> A;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
    }

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));

    for(uint32_t bucket = A.bucket_size(); bucket < 2 * A.bucket_size(); ++bucket)
    {
        ASSERT_THROW(A.begin(bucket), std::out_of_range);
        ASSERT_THROW(A.end(bucket), std::out_of_range);
    }
}

TYPED_TEST(HashTests, BucketDepthTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int, TypeParam> A;
    uint32_t maxBucketDepth = UnorderedMap<int, int, TypeParam>::getBucketDepth();

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
    }

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));

    for(uint32_t bucket = 0; bucket < A.bucket_size(); ++bucket)
    {
        uint32_t bucketDepth = 1;
        for(Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it, ++bucketDepth)
        {
            ASSERT_TRUE(bucketDepth <= maxBucketDepth);
        }
    }
}

TYPED_TEST(HashTests, BucketIteratorHashCollisionTest)
{
    const int keys[] = {1, 5, 9, 13, 17, 21, 25};
    const int keyIteratorOrder[] = {1, 17, 5, 21, 9, 25, 13};

    UnorderedMap<int, int, TypeParam> A;
    uint32_t maxBucketDepth = UnorderedMap<int, int, TypeParam>::getBucketDepth();

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
    }

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));
    uint32_t index = 0;

    for(uint32_t bucket = 0; bucket < A.bucket_size(); ++bucket)
    {
        uint32_t bucketDepth = 1;

        for(Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it, ++bucketDepth, ++index)
        {
            ASSERT_EQ(*it, keyIteratorOrder[index]);
        }

        ASSERT_TRUE(bucketDepth <= maxBucketDepth);
    }
}

TYPED_TEST(HashTests, BucketSizeTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int, TypeParam> A;

    ASSERT_EQ(A.bucket_size(), 1);

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
    }

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));

    if(std::is_same<TypeParam, IntHash2>::value)
    {
        ASSERT_EQ(A.bucket_size(), 8);
    }
    else
    {
        ASSERT_EQ(A.bucket_size(), 4);
    }
}

TYPED_TEST(HashTests, BucketIteratorOrderTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};
    const Vector<int> keyIteratorOrder = OrderGenerator<TypeParam>();

    UnorderedMap<int, int, TypeParam> A;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
    }

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));
    uint32_t index = 0;

    for(uint32_t bucket = 0; bucket < A.bucket_size(); ++bucket)
    {
        for(Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it, ++index)
        {
            ASSERT_EQ(*it, keyIteratorOrder.at(index));
        }
    }
}

TYPED_TEST(HashTests, MapIteratorOrderTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};
    const Vector<int> keyIteratorOrder = OrderGenerator<TypeParam>();

    UnorderedMap<int, int, TypeParam> A;

    for(uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
    }

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));
    uint32_t index = 0;

    for(Iterator<int> it = A.begin(); it != A.end(); ++it, ++index)
    {
        ASSERT_EQ(*it, keyIteratorOrder.at(index));
    }
}
