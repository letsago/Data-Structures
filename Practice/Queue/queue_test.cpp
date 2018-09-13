#include "queue_test.h"
#include <pyu/queue.h>

using namespace pyu;

Test_Registrar<QueueTests> QueueTests::registrar;

bool QueueTests::PushTest(LinearStorageInterface<int>* pLsi)
{
    Queue<int> A(&pLsi);

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.front(), 0);
        VERIFY_EQ(A.length(), i + 1);
    }

    delete pLsi;
    
    return true;
}

bool QueueTests::PopTest(LinearStorageInterface<int>* pLsi)
{
    Queue<int> A(&pLsi);
    VERIFY_FALSE(A.pop());

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.front(), 0);
        VERIFY_EQ(A.length(), i + 1);
    }

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_EQ(A.front(), i);
        VERIFY_TRUE(A.pop());
        VERIFY_EQ(A.length(), 4 - i);
    }

    delete pLsi;

    return true;
}

bool QueueTests::FrontTest(LinearStorageInterface<int>* pLsi)
{
    Queue<int> A(&pLsi);
    VERIFY_TRUE(A.push(0));
    VERIFY_TRUE(A.push(1));
    VERIFY_TRUE(A.push(2));
    VERIFY_EQ(A.front(), 0);
    A.front() = 6;
    VERIFY_EQ(A.front(), 6);
    delete pLsi;

    return true;
}

bool QueueTests::ClearTest(LinearStorageInterface<int>* pLsi)
{
    Queue<int> A(&pLsi);
    VERIFY_TRUE(A.empty());

    for (uint32_t i = 0; i < 5; i++)
    {
        VERIFY_TRUE(A.push(i));
        VERIFY_EQ(A.front(), 0);
        VERIFY_EQ(A.length(), i + 1);
    }

    A.clear();
    VERIFY_TRUE(A.empty());
    delete pLsi;

    return true;
}