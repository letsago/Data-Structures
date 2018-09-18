#include "linkedlist_test.h"
#include <pyu/linked_list.h>

using namespace pyu;

Test_Registrar<LinkedListTests> LinkedListTests::registrar;

bool LinkedListTests::FindManyTest()
{
    // FindMany returns a vector all positions where given value occurs in linked list
    LinkedList<int> A;

    for (uint32_t i = 0; i < 5; ++i)
    {
        A.insert_back(5);
    }
    
    Vector<int> FindIndices = A.findmany(5);
    VERIFY_EQ(FindIndices.length(), 5);

    for (uint32_t i = 0; i < FindIndices.length(); ++i)
    {
        VERIFY_EQ(FindIndices.at(i), i);
    }
    
    LinkedList<int> B;

    for (uint32_t i = 0; i < 3; ++i)
    {
        B.insert_back(i);
    }

    FindIndices = B.findmany(5);

    VERIFY_TRUE(FindIndices.empty());
    VERIFY_EQ(FindIndices.length(), 0);

    LinkedList<int> C;
    C.insert_front(1);
    C.insert_back(2);
    C.insert_back(1);

    FindIndices = C.findmany(1);

    VERIFY_EQ(FindIndices.length(), 2);
    VERIFY_EQ(FindIndices.at(0), 0);
    VERIFY_EQ(FindIndices.at(1), 2);

    return true;
}

bool LinkedListTests::AssignmentTest()
{
    LinkedList<int> A;
    A.insert_back(2);
    A.insert_back(4);

    LinkedList<int> B = A;
    A.clear();
    VERIFY_EQ(B.length(), 2);
    
    for (uint32_t i = 0; i < B.length(); ++i)
        VERIFY_EQ(B.at(i), (i + 1) * 2);
    
    LinkedList<int> C;
    B = C;
    VERIFY_EQ(B.length(), 0);
    VERIFY_TRUE(B.empty());
    
    return true;
}

bool LinkedListTests::CopyTest()
{
    LinkedList<int> A;
    A.insert_back(2);
    A.insert_back(4);

    LinkedList<int> B(A);
    A.clear();
    VERIFY_EQ(B.length(), 2);
    
    for (uint32_t i = 0; i < B.length(); ++i)
        VERIFY_EQ(B.at(i), (i + 1) * 2);
    
    LinkedList<int> C;
    VERIFY_EQ(C.length(), 0);
    VERIFY_TRUE(C.empty());

    LinkedList<int> D(C);
    VERIFY_EQ(D.length(), 0);
    VERIFY_TRUE(D.empty());
    
    return true;
}

bool LinkedListTests::IteratorTest()
{
    LinkedList<int> A;

    for (uint32_t i = 0; i < 5; ++i)
    {
        A.insert_back(i * 2);
    }

    uint32_t n = 0;
    for (LinkedList<int>::Iterator it = A.begin(); it != A.end(); ++it)
    {
        VERIFY_EQ(*it, n);
        n = n + 2;
    }

    return true;
}

