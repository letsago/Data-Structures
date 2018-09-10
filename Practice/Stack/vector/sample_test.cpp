#include "headers/sample_test.h"
#include "headers/vector_stack.h"

Test_Registrar<StackVectorTests> StackVectorTests::registrar;

bool StackVectorTests::PushTest()
{
    Stack<int> A;

    for (int i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Top(), i);
        VERIFY_EQ(A.size(), i + 1);
    }
    
    return true;
}

bool StackVectorTests::PopTest()
{
    Stack<int> A;
    VERIFY_FALSE(A.Pop());

    for (int i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Top(), i);
        VERIFY_EQ(A.size(), i + 1);
    }

    for (int i = 5; i > 0; i--)
    {
        VERIFY_EQ(A.Top(), i - 1);
        VERIFY_TRUE(A.Pop());
        VERIFY_EQ(A.size(), i - 1);
    }

    return true;
}

bool StackVectorTests::TopTest()
{
    Stack<int> A;
    VERIFY_TRUE(A.Push(5));
    VERIFY_EQ(A.Top(), 5);
    A.Top() = 6;
    VERIFY_EQ(A.Top(), 6);

    return true;
}

bool StackVectorTests::ClearTest()
{
    Stack<int> A;

    VERIFY_EQ(A.size(), 0);

    for (int i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Top(), i);
        VERIFY_EQ(A.size(), i + 1);
    }

    A.Clear();

    VERIFY_EQ(A.size(), 0);

    return true;
}

bool StackVectorTests::AssignmentTest()
{
    Stack<int> A;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Top(), i);
        VERIFY_EQ(A.size(), i + 1);
    }

    Stack<int> B = A;

    A.Clear();
    VERIFY_EQ(B.size(), 5);

    for (int i = 5; i < 0; --i)
    {
        VERIFY_EQ(B.Top(), i - 1);
        VERIFY_TRUE(B.Pop());
        VERIFY_EQ(B.size(), i - 1);
    }

    return true;
}

bool StackVectorTests::CopyTest()
{
    Stack<int> A;

    for (int i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.Push(i));
        VERIFY_EQ(A.Top(), i);
        VERIFY_EQ(A.size(), i + 1);
    }

    Stack<int> B(A);

    A.Clear();
    VERIFY_EQ(B.size(), 5);

    for (int i = 5; i < 0; --i)
    {
        VERIFY_EQ(B.Top(), i - 1);
        VERIFY_TRUE(B.Pop());
        VERIFY_EQ(B.size(), i - 1);
    }

    return true;
}