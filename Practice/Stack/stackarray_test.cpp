#include "stackarray_test.h"
#include <pyu/stack.h>
#include <pyu/shared_ptr.h>

using namespace pyu;

Test_Registrar<StackArrayTests> StackArrayTests::registrar;

bool StackArrayTests::InvalidPushTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi)
{
    Stack<int> A(pLsi);

    VERIFY_EQ(A.length(), 0);

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.top(), i);
        VERIFY_EQ(A.length(), i + 1);
    }

    VERIFY_FALSE(A.push(5));
    VERIFY_EQ(A.length(), 5);
    
    return true;
}
