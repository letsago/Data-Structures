#include <gtest/gtest.h>
#include <pyu/linked_list.h>

TEST(LinkedListTests, FindManyTest)
{
    // FindMany returns a vector all positions where given value occurs in linked list
    pyu::LinkedList<int> A;

    for(uint32_t i = 0; i < 5; ++i)
    {
        A.insert_back(5);
    }

    pyu::Vector<int> FindIndices = A.findmany(5);
    ASSERT_EQ(FindIndices.length(), 5);

    for(uint32_t i = 0; i < FindIndices.length(); ++i)
    {
        ASSERT_EQ(FindIndices.at(i), i);
    }

    pyu::LinkedList<int> B;

    for(uint32_t i = 0; i < 3; ++i)
    {
        B.insert_back(i);
    }

    FindIndices = B.findmany(5);

    ASSERT_TRUE(FindIndices.empty());
    ASSERT_EQ(FindIndices.length(), 0);

    pyu::LinkedList<int> C;
    C.insert_front(1);
    C.insert_back(2);
    C.insert_back(1);

    FindIndices = C.findmany(1);

    ASSERT_EQ(FindIndices.length(), 2);
    ASSERT_EQ(FindIndices.at(0), 0);
    ASSERT_EQ(FindIndices.at(1), 2);
}
