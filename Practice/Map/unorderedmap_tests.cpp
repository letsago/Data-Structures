#include <gtest/gtest.h>
#include <pyu/unorderedmap.h>
#include <pyu/orderedset.h>
#include <pyu/iterator.h>
#include <pyu/common.h>

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

    ASSERT_EQ(A.bucket_size(), 0);

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
        for (Iterator<int> it = A.begin(bucket); it != A.end(bucket); ++it)
        {
            ASSERT_EQ(*it, keyIteratorOrder[index]);
            ++index;
        }
    }
}