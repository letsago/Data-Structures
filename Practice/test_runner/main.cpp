#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <piglatin_test.h>
#include <linkedlist_test.h>
#include <vector_test.h>
#include <array_test.h>
#include <queue_test.h>
#include <stack_test.h>
#include <stackarray_test.h>
#include <queuearray_test.h>
#include <tree_test.h>
#include <sharedptr_test.h>

int main()
{
    // In order to disable a test simply call;
    // DISABLE_TEST(VectorTests);
    // DISABLE_TEST(LinkedListTests);
    // DISABLE_TEST(PigLatinTests);
    // DISABLE_TEST(ArrayTests);
    // DISABLE_TEST(QueueTests);
    // DISABLE_TEST(StackTests);
    // DISABLE_TEST(StackArrayTests);
    // DISABLE_TEST(QueueArrayTests);
    // DISABLE_TEST(SharedPtrTests);
    // DISABLE_TEST(TreeTests);
    UnitTests::Run_All();

    return 0;
}
