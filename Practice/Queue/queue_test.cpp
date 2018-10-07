#include <gtest/gtest.h>
#include <pyu_test/LinearStorageInterfaceCreator.h>
#include <pyu/vector.h>
#include <pyu/linked_list.h>
#include <pyu/rollingarray.h>
#include <pyu/queue.h>

template<class T>
class QueueTests : public ::testing::Test, public pyu::internal::LinearStorageInterfaceCreator<T> {};

typedef testing::Types<pyu::Vector<int>, pyu::LinkedList<int>, pyu::RollingArray<int, 10>> Implementations;
TYPED_TEST_CASE(QueueTests, Implementations);

TYPED_TEST(QueueTests, PushTest)
{
    pyu::Queue<int> A(this->CreateTestableInterface());

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.front(), 0);
        ASSERT_EQ(A.length(), i + 1);
    }
}

TYPED_TEST(QueueTests, PopTest)
{
    pyu::Queue<int> A(this->CreateTestableInterface());
    ASSERT_FALSE(A.pop());

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.front(), 0);
        ASSERT_EQ(A.length(), i + 1);
    }

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(A.front(), i);
        ASSERT_TRUE(A.pop());
        ASSERT_EQ(A.length(), 4 - i);
    }
}

TYPED_TEST(QueueTests, FrontTest)
{
    pyu::Queue<int> A(this->CreateTestableInterface());
    ASSERT_TRUE(A.push(0));
    ASSERT_TRUE(A.push(1));
    ASSERT_TRUE(A.push(2));
    ASSERT_EQ(A.front(), 0);
    A.front() = 6;
    ASSERT_EQ(A.front(), 6);
}

TYPED_TEST(QueueTests, ClearTest)
{
    pyu::Queue<int> A(this->CreateTestableInterface());
    ASSERT_TRUE(A.empty());

    for (uint32_t i = 0; i < 5; i++)
    {
        ASSERT_TRUE(A.push(i));
        ASSERT_EQ(A.front(), 0);
        ASSERT_EQ(A.length(), i + 1);
    }

    A.clear();
    ASSERT_TRUE(A.empty());
}
