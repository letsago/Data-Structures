#include <gtest/gtest.h>
#include <pyu/unorderedmap.h>
#include <pyu/orderedset.h>
#include <pyu/iterator.h>
#include <pyu/common.h>
#include <stdexcept>

using namespace pyu;

TEST(UnorderedMapTests, MapIteratorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int> A;
    OrderedSet<int> B;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
    {
        ASSERT_TRUE(A.insert(keys[i], i));
        ASSERT_TRUE(B.insert(keys[i]));
    }

    ASSERT_EQ(A.size(), B.size());

    for (Iterator<int> it = A.begin(); it != A.end(); ++it)
        ASSERT_TRUE(B.remove(*it));
}

TEST(UnorderedMapTests, BucketSizeTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int> A;

    ASSERT_EQ(A.bucket_size(), 1);

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));
    ASSERT_EQ(A.bucket_size(), 4);
}

TEST(UnorderedMapTests, BucketIteratorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};
    const int keyIteratorOrder[] = {8, 20, 1, 5, 18, 10, 2, 23, 31, 15};

    UnorderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));
    uint32_t index = 0;

    for (uint32_t bucket = 0; bucket < A.bucket_size(); ++bucket)
    {
        for (Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it, ++index)
            ASSERT_EQ(*it, keyIteratorOrder[index]);
    }
}

TEST(UnorderedMapTests, BucketIteratorHashCollisionTest)
{
    const int keys[] = {1, 5, 9, 13, 17, 21, 25};
    const int keyIteratorOrder[] = {1, 17, 5, 21, 9, 25, 13};

    UnorderedMap<int, int> A;
    uint32_t maxBucketDepth = UnorderedMap<int, int>::getBucketDepth();

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));
    uint32_t index = 0;

    for (uint32_t bucket = 0; bucket < A.bucket_size(); ++bucket)
    {
        uint32_t bucketDepth = 1;

        for (Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it, ++bucketDepth, ++index)
        {
            ASSERT_EQ(*it, keyIteratorOrder[index]);
        }

        ASSERT_TRUE(bucketDepth <= maxBucketDepth);
    }
}

TEST(UnorderedMapTests, OutofRangeBucketIteratorTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int> A;

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));

    for (uint32_t bucket = A.bucket_size(); bucket < 2 * A.bucket_size(); ++bucket)
    {
        ASSERT_THROW(A.begin(bucket), std::out_of_range);
        ASSERT_THROW(A.end(bucket), std::out_of_range);
    }
}

TEST(UnorderedMapTests, BucketDepthTest)
{
    const int keys[] = {10, 20, 15, 8, 2, 5, 31, 1, 18, 23};

    UnorderedMap<int, int> A;
    uint32_t maxBucketDepth = UnorderedMap<int, int>::getBucketDepth();

    for (uint32_t i = 0; i < ARRAYSIZE(keys); ++i)
        ASSERT_TRUE(A.insert(keys[i], i));

    ASSERT_EQ(A.size(), ARRAYSIZE(keys));

    for (uint32_t bucket = 0; bucket < A.bucket_size(); ++bucket)
    {
        uint32_t bucketDepth = 1;
        for (Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it, ++bucketDepth)
        ASSERT_TRUE(bucketDepth <= maxBucketDepth);
    }
}
