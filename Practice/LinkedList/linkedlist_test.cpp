#include "linkedlist_test.h"
#include <pyu/linked_list.h>

using namespace pyu;

Test_Registrar<LinkedListTests> LinkedListTests::registrar;

bool LinkedListTests::InsertTest()
{
    LinkedList<int> A;
    VERIFY_FALSE(A.Insert(1, 3));

    LinkedList<int> B;

    for (int i = 0; i < 8; ++i)
    {
        VERIFY_TRUE(B.Insert(i, i));
        VERIFY_EQ(B.Length(), i + 1);
    }

    for (int i = 0; i < B.Length(); ++i)
    {
        VERIFY_EQ(B.At(i), i);
    }
    
    VERIFY_FALSE(B.Insert(9, 9));

    return true;
}

bool LinkedListTests::RemoveTest()
{
    LinkedList<int> A;
    VERIFY_FALSE(A.Remove(0));

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Insert(i, i));
        VERIFY_EQ(A.At(i), i);
        VERIFY_EQ(A.Length(), i + 1);
    }

    VERIFY_TRUE(A.Remove(3));
    VERIFY_EQ(A.Length(), 4);
    
    for (int i = 0; i < 3; ++i)
    {
        VERIFY_EQ(A.At(i), i);
    }

    VERIFY_EQ(A.At(3), 4);

    return true;
}

bool LinkedListTests::InsertFrontTest()
{
    LinkedList<int> A;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Insert_front(i * 2));
        VERIFY_EQ(A.Front(), i * 2);
        VERIFY_EQ(A.Length(), i + 1);
    }
    
    for (int i = 0; i < 5; ++i)
    {
        VERIFY_EQ(A.At(i), (4 - i) * 2);
    }

    return true;
}

bool LinkedListTests::RemoveFrontTest()
{
    LinkedList<int> A;
    VERIFY_FALSE(A.Remove_front());

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Insert_front(i * 2));
        VERIFY_EQ(A.Front(), i * 2);
        VERIFY_EQ(A.Length(), i + 1);
    }

    for (int i = 5; i > 0; --i)
    {
        VERIFY_EQ(A.Front(), (i - 1) * 2);
        VERIFY_TRUE(A.Remove_front());
        VERIFY_EQ(A.Length(), i - 1);
    }

    return true;
}

bool LinkedListTests::InsertBackTest()
{
    LinkedList<int> A;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Insert_back(i * 3));
        VERIFY_EQ(A.Length(), i + 1);
    }

    for (int i = 0; i < A.Length(); ++i)
    {
        VERIFY_EQ(A.At(i), i * 3);
    }

    return true;
}

bool LinkedListTests::RemoveBackTest()
{
    LinkedList<int> A;
    VERIFY_FALSE(A.Remove_front());

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Insert_back(i * 3));
        VERIFY_EQ(A.Back(), i * 3);
        VERIFY_EQ(A.Length(), i + 1);
    }

    for (int i = 5; i > 0; --i)
    {
        VERIFY_EQ(A.Back(), (i - 1) * 3);
        VERIFY_TRUE(A.Remove_back());
        VERIFY_EQ(A.Length(), i - 1);
    }

    return true;
}

bool LinkedListTests::FindFirstTest()
{
    LinkedList<int> A;

    VERIFY_EQ(A.FindFirst(0), -1);

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Insert_back(i));
    }

    // Find succeeds if able to find index of given value
    for (int i = 0; i < 5; ++i)
    {
        VERIFY_EQ(A.FindFirst(i), i);
    }
    
    VERIFY_TRUE(A.Insert(2, 4));

    // Find will return the index of first instance of value
    VERIFY_EQ(A.FindFirst(4), 2);

    // If unable to find index of given value, Find fails and returns -1
    VERIFY_EQ(A.FindFirst(8), -1);

    return true;
}

bool LinkedListTests::FindManyTest()
{
    // FindMany returns a vector all positions where given value occurs in linked list
    LinkedList<int> A;

    for (int i = 0; i < 5; ++i)
    {
        A.Insert_back(5);
    }
    
    Vector<int> FindIndices = A.FindMany(5);
    VERIFY_EQ(FindIndices.Length(), 5);

    for (int i = 0; i < FindIndices.Length(); ++i)
    {
        VERIFY_EQ(FindIndices.At(i), i);
    }
    
    LinkedList<int> B;

    for (int i = 0; i < 3; ++i)
    {
        B.Insert_back(i);
    }

    FindIndices = B.FindMany(5);

    VERIFY_TRUE(FindIndices.Empty());
    VERIFY_EQ(FindIndices.Length(), 0);

    LinkedList<int> C;
    C.Insert_front(1);
    C.Insert_back(2);
    C.Insert_back(1);

    FindIndices = C.FindMany(1);

    VERIFY_EQ(FindIndices.Length(), 2);
    VERIFY_EQ(FindIndices.At(0), 0);
    VERIFY_EQ(FindIndices.At(1), 2);

    return true;
}

bool LinkedListTests::ClearTest()
{
    LinkedList<int> A;

    for (int i = 0; i < 5; ++i)
    {
        A.Insert_back(5);
    }

    VERIFY_EQ(A.Length(), 5);

    A.Clear();
    VERIFY_TRUE(A.isEmpty());
    VERIFY_EQ(A.Length(), 0);
    
    return true;
}

bool LinkedListTests::AssignmentOperatorTest()
{
    LinkedList<int> A;
    A.Insert_back(2);
    A.Insert_back(4);

    LinkedList<int> B = A;
    A.Clear();
    VERIFY_EQ(B.Length(), 2);
    
    for (int i = 0; i < B.Length(); ++i)
        VERIFY_EQ(B.At(i), (i + 1) * 2);
    
    LinkedList<int> C;
    B = C;
    VERIFY_EQ(B.Length(), 0);
    VERIFY_TRUE(B.isEmpty());
    
    return true;
}

bool LinkedListTests::CopyTest()
{
    LinkedList<int> A;
    A.Insert_back(2);
    A.Insert_back(4);

    LinkedList<int> B(A);
    A.Clear();
    VERIFY_EQ(B.Length(), 2);
    
    for (int i = 0; i < B.Length(); ++i)
        VERIFY_EQ(B.At(i), (i + 1) * 2);
    
    LinkedList<int> C;
    VERIFY_EQ(C.Length(), 0);
    VERIFY_TRUE(C.isEmpty());

    LinkedList<int> D(C);
    VERIFY_EQ(D.Length(), 0);
    VERIFY_TRUE(D.isEmpty());
    
    return true;
}

bool LinkedListTests::AtTest()
{
    LinkedList<int> A;

    for (int i = 0; i < 8; ++i)
    {
        A.Insert_back(8);
    }

    A.At(4) = 5;
    VERIFY_EQ(A.At(4), 5);
    A.Front() = 1;
    VERIFY_EQ(A.Front(), 1);
    A.Back() = 10;
    VERIFY_EQ(A.Back(), 10);

    return true;
}