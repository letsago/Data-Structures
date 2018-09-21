#include "stack_test.h"
#include <pyu/stack.h>
#include <pyu/shared_ptr.h>

using namespace pyu;

Test_Registrar<StackTests> StackTests::registrar;

bool StackTests::PushTest(shared_ptr<LinearStorageInterface<int>> pLsi)
{
    Stack<int> A(pLsi);

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.top(), i);
        VERIFY_EQ(A.length(), i + 1);
    }
    
    return true;
}

bool StackTests::PopTest(shared_ptr<LinearStorageInterface<int>> pLsi)
{
    Stack<int> A(pLsi);
    VERIFY_FALSE(A.pop());

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.top(), i);
        VERIFY_EQ(A.length(), i + 1);
    }

    for (uint32_t i = 5; i > 0; i--)
    {
        VERIFY_EQ(A.top(), i - 1);
        VERIFY_TRUE(A.pop());
        VERIFY_EQ(A.length(), i - 1);
    }

    VERIFY_TRUE(A.empty());

    return true;
}

bool StackTests::TopTest(shared_ptr<LinearStorageInterface<int>> pLsi)
{
    Stack<int> A(pLsi);
    VERIFY_TRUE(A.push(5));
    VERIFY_EQ(A.top(), 5);
    A.top() = 6;
    VERIFY_EQ(A.top(), 6);

    return true;
}

bool StackTests::ClearTest(shared_ptr<LinearStorageInterface<int>> pLsi)
{
    Stack<int> A(pLsi);

    VERIFY_TRUE(A.empty());

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.top(), i);
        VERIFY_EQ(A.length(), i + 1);
    }

    A.clear();

    VERIFY_TRUE(A.empty());

    return true;
}