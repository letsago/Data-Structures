#include <gtest/gtest.h>
#include <pyu/array.h>

TEST(ArrayTests, StaticMemoryTest)
{
    pyu::Array<int, 5> A;

    ASSERT_EQ(A.capacity(), 5);
    ASSERT_EQ(A.length(), 0);

    for (uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(A.insert_back(i));
        ASSERT_EQ(A.capacity(), 5);
        ASSERT_EQ(A.length(), i + 1);
    }

    ASSERT_FALSE(A.insert_back(6));
}
