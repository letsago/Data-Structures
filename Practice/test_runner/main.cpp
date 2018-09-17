#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <piglatin_test.h>
#include <linkedlist_test.h>
#include <vector_test.h>
#include <array_test.h>
#include <queue_test.h>
#include <stack_test.h>

int main()
{
    // In order to disable a test simply call;
    // DISABLE_TEST(VectorTests);
    UnitTests::Run_All();

    return 0;
}
