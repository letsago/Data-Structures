#include "queuearray_test.h"
#include <pyu/queue.h>

using namespace pyu;

Test_Registrar<QueueArrayTests> QueueArrayTests::registrar;

bool QueueArrayTests::InvalidPushTest(LinearStorageInterface<int>* pLsi)
{
    Queue<int> A(&pLsi);
    VERIFY_EQ(A.length(), 0);

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.front(), 0);
        VERIFY_EQ(A.length(), i + 1);
    }

    VERIFY_FALSE(A.push(5));
    VERIFY_EQ(A.length(), 5);
    delete pLsi;
    
    return true;
}

bool QueueArrayTests::RollingPopTest(LinearStorageInterface<int>* pLsi)
{
    Queue<int> A(&pLsi);
    VERIFY_FALSE(A.pop());

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.front(), 0);
        VERIFY_EQ(A.length(), i + 1);
    }

    VERIFY_TRUE(A.pop());
    VERIFY_EQ(A.front(), 1);
    VERIFY_EQ(A.length(), 4);
    VERIFY_TRUE(A.push(5));
    VERIFY_EQ(A.front(), 1);
    VERIFY_EQ(A.length(), 5);
    delete pLsi;

    return true;
}
