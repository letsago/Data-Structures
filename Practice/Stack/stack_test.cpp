#include "stack_test.h"
#include <pyu/vector.h>
#include <pyu/linked_list.h>
#include <pyu/array.h>
#include <pyu/stack.h>

typedef testing::Types<pyu::Vector<int>, pyu::LinkedList<int>, pyu::Array<int, 10>> Implementations;
TYPED_TEST_CASE(StackTests, Implementations);

TYPED_TEST(StackTests, PushTest)
{
    pyu::Stack<int> A(this->CreateTestableInterface());

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.top(), i);
        ASSERT_EQ(A.length(), i + 1);
    }
}

TYPED_TEST(StackTests, PopTest)
{
    pyu::Stack<int> A(this->CreateTestableInterface());
    ASSERT_FALSE(A.pop());

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.top(), i);
        ASSERT_EQ(A.length(), i + 1);
    }

    for (uint32_t i = 5; i > 0; i--)
    {
        ASSERT_EQ(A.top(), i - 1);
        ASSERT_TRUE(A.pop());
        ASSERT_EQ(A.length(), i - 1);
    }

    ASSERT_TRUE(A.empty());
}

TYPED_TEST(StackTests, TopTest)
{
    pyu::Stack<int> A(this->CreateTestableInterface());
    ASSERT_TRUE(A.push(5));
    ASSERT_EQ(A.top(), 5);
    A.top() = 6;
    ASSERT_EQ(A.top(), 6);
}

TYPED_TEST(StackTests, ClearTest)
{
    pyu::Stack<int> A(this->CreateTestableInterface());

    ASSERT_TRUE(A.empty());

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.top(), i);
        ASSERT_EQ(A.length(), i + 1);
    }

    A.clear();
    ASSERT_TRUE(A.empty());
}