#include "array_test.h"
#include <pyu/array.h>

using namespace pyu;

Test_Registrar<ArrayTests> ArrayTests::registrar;

bool ArrayTests::StaticMemoryTest()
{
    Array<int, 5> A;

    VERIFY_EQ(A.capacity(), 5);
    VERIFY_EQ(A.length(), 0);

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(A.insert_back(i));
        VERIFY_EQ(A.capacity(), 5);
        VERIFY_EQ(A.length(), i + 1);
    }

    VERIFY_FALSE(A.insert_back(6));

    return true;
}