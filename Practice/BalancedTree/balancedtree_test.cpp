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

    uint32_t depth = A.depth();
    ASSERT_TRUE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, NonBalancedTest)
{
    const int arr[] = {10, 5, 20, 2, 1};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    uint32_t depth = A.depth();
    ASSERT_FALSE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, RightSkewedTest)
{
    const int arr[] = {11, 12, 13, 14};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    uint32_t depth = A.depth();
    ASSERT_FALSE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, LeftSkewedTest)
{
    const int arr[] = {14, 13, 12, 11};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    uint32_t depth = A.depth();
    ASSERT_FALSE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, BigBalancedTest)
{
    const int arr[] = {50, 25, 12, 38, 6, 3, 9, 18, 15, 22, 30, 26, 35, 42, 40, 48, 100, 75, 60, 55, 65, 85, 80, 90, 150, 175, 200, 160, 125, 108, 130};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
    }

    uint32_t depth = A.depth();
    ASSERT_TRUE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, BigNonBalancedTest)
{
    const int arr[] = {28, 12, 6, 80, 43, 586, 100, 19, 29, 81, 25, 21, 34, 15};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
    }

    uint32_t depth = A.depth();
    ASSERT_FALSE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, NullTest)
{
    Tree<int> A;
    uint32_t depth = A.depth();
    ASSERT_TRUE(A.isBalanced(depth));
}

TEST(BalancedTreeTests, InsertRightSkewedTest)
{
    const int arr[] = {11, 12, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertLeftSkewedTest)
{
    const int arr[] = {14, 13, 12};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertLeftAngleTest)
{
    const int arr[] = {14, 12, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertRightAngleTest)
{
    const int arr[] = {12, 14, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeLeftSkewedTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 1};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeLeftAngleTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 3};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeRightAngleTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 6};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertLeftSubtreeRightSkewedTest)
{
    const int arr[] = {10, 5, 15, 2, 8, 12, 9};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeLeftSkewedTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 11};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeLeftAngleTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeRightAngleTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 18};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertRightSubtreeRightSkewedTest)
{
    const int arr[] = {10, 5, 15, 8, 12, 20, 23};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        A.insert(arr[i]);
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}

TEST(BalancedTreeTests, InsertBigNonBalancedTest)
{
    const int arr[] = {28, 12, 6, 80, 43, 586, 100, 19, 29, 81, 25, 21, 34, 15, 13};

    BalancedTree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
        uint32_t depth = A.depth();
        ASSERT_TRUE(A.isBalanced(depth));
    }
}