#include "headers/sample_test.h"
#include "headers/vector_queue.h"

Test_Registrar<QueueVectorTests> QueueVectorTests::registrar;

bool QueueVectorTests::PushTest()
{
    Queue<int> A;

    for (int i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Front(), 0);
        VERIFY_EQ(A.size(), i + 1);
    }
    
    return true;
}

bool QueueVectorTests::PopTest()
{
    Queue<int> A;
    VERIFY_FALSE(A.Pop());

    for (int i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Front(), 0);
        VERIFY_EQ(A.size(), i + 1);
    }

    for (int i = 0; i < 5; i++)
    {
        VERIFY_EQ(A.Front(), i);
        VERIFY_TRUE(A.Pop());
        VERIFY_EQ(A.size(), 4 - i);
    }

    return true;
}

bool QueueVectorTests::FrontTest()
{
    Queue<int> A;
    VERIFY_TRUE(A.Push(0));
    VERIFY_TRUE(A.Push(1));
    VERIFY_TRUE(A.Push(2));
    VERIFY_EQ(A.Front(), 0);
    A.Front() = 6;
    VERIFY_EQ(A.Front(), 6);

    return true;
}

bool QueueVectorTests::ClearTest()
{
    Queue<int> A;

    VERIFY_TRUE(A.isEmpty());

    for (int i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Front(), 0);
        VERIFY_EQ(A.size(), i + 1);
    }

    A.Clear();

    VERIFY_TRUE(A.isEmpty());

    return true;
}

bool QueueVectorTests::AssignmentTest()
{
    Queue<int> A;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Front(), 0);
        VERIFY_EQ(A.size(), i + 1);
    }

    Queue<int> B = A;

    A.Clear();
    VERIFY_EQ(B.size(), 5);
    VERIFY_EQ(A.size(), 0);

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_EQ(B.Front(), i);
        VERIFY_TRUE(B.Pop());
        VERIFY_EQ(B.size(), 4 - i);
    }

    Queue<int> C;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(C.Push(i * 2));
        VERIFY_EQ(C.Front(), 0);
        VERIFY_EQ(C.size(), i + 1);
    }

    C = B;

    VERIFY_TRUE(C.isEmpty());

    return true;
}

bool QueueVectorTests::CopyTest()
{
    Queue<int> A;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Front(), 0);
        VERIFY_EQ(A.size(), i + 1);
    }

    Queue<int> B(A);

    A.Clear();
    VERIFY_EQ(B.size(), 5);
    VERIFY_TRUE(A.isEmpty());

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_EQ(B.Front(), i);
        VERIFY_TRUE(B.Pop());
        VERIFY_EQ(B.size(), 4 - i);
    }

    VERIFY_TRUE(B.isEmpty());

    Queue<int> C(B);
    VERIFY_TRUE(C.isEmpty());
    
    return true;
}