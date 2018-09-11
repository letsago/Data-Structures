#include "stack_test.h"
#include <pyu/vector_stack.h>

using namespace pyu;

Test_Registrar<StackTests> StackTests::registrar;

bool StackTests::PushTest()
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

bool StackTests::PopTest()
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

bool StackTests::TopTest()
{
    Stack<int> A;
    VERIFY_TRUE(A.Push(5));
    VERIFY_EQ(A.Top(), 5);
    A.Top() = 6;
    VERIFY_EQ(A.Top(), 6);

    return true;
}

bool StackTests::ClearTest()
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

bool StackTests::AssignmentTest()
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

bool StackTests::CopyTest()
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