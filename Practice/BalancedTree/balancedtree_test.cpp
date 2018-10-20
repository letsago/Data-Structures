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
        ASSERT_TRUE(A.insert(arr[i]));
    }

    ASSERT_FALSE(A.isBalanced());
}

TEST(BalancedTreeTests, NullTest)
{
    Tree<int> A;

    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, InsertRightSkewedTest)
{
    const int arr[] = {11, 12, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertLeftSkewedTest)
{
    const int arr[] = {14, 13, 12};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertLeftAngleTest)
{
    const int arr[] = {14, 12, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertRightAngleTest)
{
    const int arr[] = {12, 14, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeLeftSkewedTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 1};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeLeftAngleTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 3};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeRightAngleTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 6};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeRightSkewedTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 9};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeLeftSkewedTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 11};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeLeftAngleTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeRightAngleTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 18};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeRightSkewedTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 23};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, InsertBigNonBalancedTest)
{
    const int arr[] = {28, 12, 6, 80, 43, 586, 100, 19, 29, 81, 25, 21, 34, 15, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }
}

TEST(BalancedTreeTests, RemoveLeftSkewedTest)
{
    const int arr[] = {20, 10, 30, 5};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(30));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveLeftAngleTest)
{
    const int arr[] = {20, 10, 30, 15};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));

        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(30));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveRightAngleTest)
{
    const int arr[] = {20, 10, 30, 25};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(10));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveRightSkewedTest)
{
    const int arr[] = {20, 10, 30, 35};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(10));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveLeftSubtreeTest)
{
    const int arr[] = {20, 10, 30, 5, 15, 25, 35, 22, 28, 38};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(10));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(15));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(5));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveRightSubtreeTest)
{
    const int arr[] = {20, 10, 30, 5, 15, 25, 35, 2, 8, 18};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(30));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(35));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(25));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveBiggerRightSubtreeTest)
{
    const int arr[] = {20, 10, 30, 5, 15, 25, 35, 2, 8, 12, 18, 22, 28, 32, 40, 1, 3, 9, 11, 13, 17, 19};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(30));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(28));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(25));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(22));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(32));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(35));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(40));
    ASSERT_TRUE(A.isBalanced());
}

TEST(BalancedTreeTests, RemoveBiggerLeftSubtreeTest)
{
    const int arr[] = {20, 10, 30, 5, 15, 25, 35, 2, 8, 12, 18, 22, 28, 32, 40, 21, 23, 26, 29, 31, 33, 38};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        ASSERT_TRUE(A.isBalanced());
    }

    ASSERT_TRUE(A.remove(10));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(8));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(5));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(2));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(12));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(15));
    ASSERT_TRUE(A.isBalanced());
    ASSERT_TRUE(A.remove(18));
    ASSERT_TRUE(A.isBalanced());
}