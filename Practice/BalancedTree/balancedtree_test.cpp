#include <gtest/gtest.h>
#include <pyu/balancedtree.h>

using namespace pyu;

TEST(BalancedTreeTests, BalancedTest)
{
    const int arr[] = {10, 5, 20, 15, 8, 2};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, NonBalancedTest)
{
    const int arr[] = {10, 5, 20, 2, 1};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    ASSERT_FALSE(A.isBalanced());
}

TEST(BalancedTreeTests, RightSkewedTest)
{
    const int arr[] = {11, 12, 13, 14};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    ASSERT_FALSE(A.isBalanced());
}

TEST(BalancedTreeTests, LeftSkewedTest)
{
    const int arr[] = {14, 13, 12, 11};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    ASSERT_FALSE(A.isBalanced());
}

TEST(BalancedTreeTests, BigBalancedTest)
{
    const int arr[] = {50, 25, 12, 38, 6, 3, 9, 18, 15, 22, 30, 26, 35, 42, 40, 48, 100, 75, 60, 55, 65, 85, 80, 90, 150, 175, 200, 160, 125, 108, 130};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, BigNonBalancedTest)
{
    const int arr[] = {28, 12, 6, 80, 43, 586, 100, 19, 29, 81, 25, 21, 34, 15};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    ASSERT_FALSE(A.isBalanced());
}

TEST(BalancedTreeTests, NullTest)
{
    Tree<int> A;
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, InsertTest)
{
    const int arr[] = {11, 12, 13, 14};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }
}
