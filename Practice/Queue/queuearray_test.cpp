#include <gtest/gtest.h>
#include <pyu/queue.h>
#include <pyu/rollingarray.h>
#include <pyu_test/LinearStorageInterfaceCreator.h>

class QueueArrayTests : public ::testing::Test,
                        public pyu::internal::LinearStorageInterfaceCreator<pyu::RollingArray<int, 5>>
{
};

TEST_F(QueueArrayTests, InvalidPushTest)
{
    pyu::Queue<int> A(this->CreateTestableInterface());
    ASSERT_EQ(A.length(), 0);

    for(uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.front(), 0);
        ASSERT_EQ(A.length(), i + 1);
    }

    ASSERT_FALSE(A.push(5));
    ASSERT_EQ(A.length(), 5);
}

TEST_F(QueueArrayTests, RollingPopTest)
{
    pyu::Queue<int> A(this->CreateTestableInterface());
    ASSERT_FALSE(A.pop());

    for(uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.front(), 0);
        ASSERT_EQ(A.length(), i + 1);
    }

    ASSERT_TRUE(A.pop());
    ASSERT_EQ(A.front(), 1);
    ASSERT_EQ(A.length(), 4);
    ASSERT_TRUE(A.push(5));
    ASSERT_EQ(A.front(), 1);
    ASSERT_EQ(A.length(), 5);
}
