#include <gtest/gtest.h>
#include <pyu_test/LinearStorageInterfaceCreator.h>
#include <pyu/stack.h>
#include <pyu/array.h>

class StackArrayTests : public ::testing::Test, public pyu::internal::LinearStorageInterfaceCreator<pyu::Array<int, 5>> {};

TEST_F(StackArrayTests, InvalidPushTest)
{
    pyu::Stack<int> A(this->CreateTestableInterface());

    ASSERT_EQ(A.length(), 0);

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.top(), i);
        ASSERT_EQ(A.length(), i + 1);
    }

    ASSERT_FALSE(A.push(5));
    ASSERT_EQ(A.length(), 5);
}
