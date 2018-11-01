#include "tree_test.h"
#include <pyu/tree.h>
#include <sstream>

using namespace pyu;

TEST(TreeTests, InsertTest)
{
    const int arr[] = {10, 5, 20, 15, 8, 2};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }

    ASSERT_FALSE(A.insert(10));
    ASSERT_FALSE(A.insert(8));
    ASSERT_FALSE(A.insert(2));
}

TEST(TreeTests, RemoveFailTest)
{
    const int arr[] = {10, 5, 20};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    ASSERT_FALSE(A.remove(8));

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_FALSE(A.remove(15));
}

TEST(TreeTests, RemoveLastLeafTest)
{
    const int arr[] = {10, 11, 12};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(12));
    data.remove(data.find(12));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRightSkewedMiddleLeafTest)
{
    const int arr[] = {10, 11, 12};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(11));
    data.remove(data.find(11));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRightAngularMiddleLeafTest)
{
    const int arr[] = {10, 12, 11};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(12));
    data.remove(data.find(12));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveLeftAngularMiddleLeafTest)
{
    const int arr[] = {10, 8, 9};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(8));
    data.remove(data.find(8));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveLeftSkewedMiddleLeafTest)
{
    const int arr[] = {10, 9, 8};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(9));
    data.remove(data.find(9));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRightSkewedRootTest)
{
    const int arr[] = {10, 11, 12};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRightAngularRootTest)
{
    const int arr[] = {10, 12, 11};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveLeftAngularRootTest)
{
    const int arr[] = {10, 8, 9};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveLeftSkewedRootTest)
{
    const int arr[] = {10, 9, 8};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveSimpleRootTest)
{
    const int arr[] = {10, 8, 12};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveMultipleRootsBalancedTest)
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }

    ASSERT_FALSE(A.remove(10));
    ASSERT_TRUE(A.remove(8));
    data.remove(data.find(8));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRootNonBalancedTest)
{
    const int arr[] = {10, 5, 15, 3, 7, 12, 20, 9, 11, 13, 8};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(10));
    data.remove(data.find(10));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRootLeftChildNonBalancedTest)
{
    const int arr[] = {10, 5, 15, 3, 7, 12, 20, 9, 11, 13, 8};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(5));
    data.remove(data.find(5));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, RemoveRootRightChildNonBalancedTest)
{
    const int arr[] = {10, 5, 15, 3, 7, 12, 20, 9, 11, 13, 8};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());
    ASSERT_TRUE(A.remove(15));
    data.remove(data.find(15));
    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }
}

TEST(TreeTests, ClearTest)
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 1, 7, 9, 40, 30, 42, 28, 35, 26, 46, 50};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());

    A.clear();
    ASSERT_TRUE(A.empty());

    Tree<int> B;
    B.clear();
    ASSERT_TRUE(B.empty());
}

TEST(TreeTests, ContainsTest)
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 90, 34, -3, -10};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.size(), data.length());

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.contains(data.at(i)));
    }

    ASSERT_FALSE(A.contains(100));
    ASSERT_FALSE(A.contains(0));
    ASSERT_FALSE(A.contains(-100));
}

TEST_F(SortedTreeTests, BalancedTree)
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 12, 18};

    Tree<int> A;

    for(uint32_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return validateSorted(A, sorted);
}

TEST_F(SortedTreeTests, NonBalancedTree)
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 90, 34, -3, -10};

    Tree<int> A;

    for(uint32_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return validateSorted(A, sorted);
}

TEST_F(SortedTreeTests, RightSkewedTree)
{
    const int arr[] = {10, 5, 20, 15, 25, 324, 90, 34};

    Tree<int> A;

    for(uint32_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return validateSorted(A, sorted);
}

TEST_F(SortedTreeTests, LeftSkewedTree)
{
    const int arr[] = {10, 5, 20, 8, 2, 1, 3, -3, -10};

    Tree<int> A;

    for(uint32_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        ASSERT_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return validateSorted(A, sorted);
}

TEST(TreeTests, SortedNullTreeTest)
{
    Tree<int> A;

    ASSERT_TRUE(A.getSorted().empty());
}

TEST(TreeTests, DepthInsertTest)
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));
    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.depth(), 3);
    ASSERT_TRUE(A.insert(30));
    ASSERT_EQ(A.depth(), 4);
    ASSERT_TRUE(A.insert(1));
    ASSERT_EQ(A.depth(), 4);
    ASSERT_TRUE(A.insert(28));
    ASSERT_EQ(A.depth(), 5);
}

TEST(TreeTests, BottomTopDepthRemoveTest)
{
    const int arr[] = {10, 15, 5};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));
    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.depth(), 2);
    ASSERT_TRUE(A.remove(5));
    ASSERT_EQ(A.depth(), 2);
    ASSERT_TRUE(A.remove(15));
    ASSERT_EQ(A.depth(), 1);
    ASSERT_TRUE(A.remove(10));
    ASSERT_EQ(A.depth(), 0);
}

TEST(TreeTests, TopBottomDepthRemoveTest)
{
    const int arr[] = {10, 5, 20, 2, 8, 15};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));
    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        ASSERT_TRUE(A.insert(data.at(i)));
    }

    ASSERT_EQ(A.depth(), 3);
    ASSERT_TRUE(A.remove(10));
    ASSERT_EQ(A.depth(), 3);
    ASSERT_TRUE(A.remove(8));
    ASSERT_EQ(A.depth(), 3);
    ASSERT_TRUE(A.remove(5));
    ASSERT_EQ(A.depth(), 3);
    ASSERT_TRUE(A.remove(2));
    ASSERT_EQ(A.depth(), 2);
    ASSERT_TRUE(A.remove(15));
    ASSERT_EQ(A.depth(), 1);
    ASSERT_TRUE(A.remove(20));
    ASSERT_EQ(A.depth(), 0);
}

TEST(TreeTests, DepthNullTreeTest)
{
    Tree<int> B;
    ASSERT_EQ(B.depth(), 0);
}

TEST(TreeTests, DepthClearTest)
{
    const int arr2[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 90, 34, -3, -10};
    Vector<int> data2(arr2, sizeof(arr2) / sizeof(arr2[0]));
    Tree<int> C;

    for(uint32_t i = 0; i < data2.length(); ++i)
    {
        ASSERT_TRUE(C.insert(data2.at(i)));
    }

    ASSERT_EQ(C.depth(), 6);
    C.clear();
    ASSERT_EQ(C.depth(), 0);
}

TEST(TreeTests, PrintSimplestTreeTest)
{
    Tree<int> A;

    A.insert(2);

    std::stringstream ss1;
    ss1 << " 2 " << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintBalancedTreeTest)
{
    const int arr[] = {4, 2, 6, 1, 3, 5, 10};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i) * 100000);
    }

    std::stringstream ss1;
    ss1 << "                     400000                      " << std::endl
        << "               _________|_________               " << std::endl
        << "              /                   \\              " << std::endl
        << "       200000                      600000        " << std::endl
        << "        __|__                       __|__        " << std::endl
        << "       /     \\                     /     \\       " << std::endl
        << "100000        300000        500000        1000000" << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintNonBalancedTreeTest)
{
    const int arr[] = {10, 5, 20, 8, 2, 25, 15, 23, 12, 18, 30};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1 << "                  10                      " << std::endl
        << "          _________|_________             " << std::endl
        << "         /                   \\            " << std::endl
        << "       5                      20          " << std::endl
        << "    ___|___                 ___|___       " << std::endl
        << "   /       \\               /       \\      " << std::endl
        << " 2           8          15          25    " << std::endl
        << "                         |           |    " << std::endl
        << "                        / \\         / \\   " << std::endl
        << "                     12    18    23    30 " << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintBigBalancedTreeTest)
{
    const int arr[] = {50,  25, 12, 38, 6,  3,  9,  18, 15,  22,  30,  26,  35,  42,  40, 48,
                       100, 75, 60, 55, 65, 85, 80, 90, 150, 175, 200, 160, 125, 108, 130};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1 << "                                             50                                              " << std::endl
        << "                         _____________________|_____________________                         " << std::endl
        << "                        /                                           \\                        " << std::endl
        << "                     25                                              100                     " << std::endl
        << "             _________|_________                             _________|_________             " << std::endl
        << "            /                   \\                           /                   \\            "
        << std::endl
        << "         12                      38                      75                      150         " << std::endl
        << "       ___|___                 ___|___                 ___|___                 ___|___       " << std::endl
        << "      /       \\               /       \\               /       \\               /       \\      "
        << std::endl
        << "    6          18          30          42          60          85          125         175   " << std::endl
        << "    |           |           |           |           |           |           |           |    " << std::endl
        << "   / \\         / \\         / \\         / \\         / \\         / \\         / \\         / \\   "
        << std::endl
        << " 3     9    15    22    26    35    40    48    55    65    80    90    108   130   160   200" << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintBigNonBalancedTreeTest)
{
    const int arr[] = {28, 12, 6, 80, 43, 586, 100, 19, 29, 81, 25, 21, 34, 15};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1 << "                                    28                                     " << std::endl
        << "                _____________________|_____________________                " << std::endl
        << "               /                                           \\               " << std::endl
        << "            12                                              80             " << std::endl
        << "    _________|_________                             _________|_________    " << std::endl
        << "   /                   \\                           /                   \\   " << std::endl
        << " 6                      19                      43                      586" << std::endl
        << "                      ___|___                 ___|                    ___| " << std::endl
        << "                     /       \\               /                       /     " << std::endl
        << "                  15          25          29                      100      " << std::endl
        << "                               |           |                       |       " << std::endl
        << "                              /             \\                     /        " << std::endl
        << "                           21                34                81          " << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintRightSkewedTreeTest)
{
    const int arr[] = {11, 12, 13, 14};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1 << "11                      " << std::endl
        << " |_________             " << std::endl
        << "           \\            " << std::endl
        << "            12          " << std::endl
        << "             |___       " << std::endl
        << "                 \\      " << std::endl
        << "                  13    " << std::endl
        << "                   |    " << std::endl
        << "                    \\   " << std::endl
        << "                     14 " << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintLeftSkewedTreeTest)
{
    const int arr[] = {14, 13, 12, 11};
    Vector<int> data(arr, sizeof(arr) / sizeof(arr[0]));

    Tree<int> A;

    for(uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1 << "                     14 " << std::endl
        << "             _________| " << std::endl
        << "            /           " << std::endl
        << "         13             " << std::endl
        << "       ___|             " << std::endl
        << "      /                 " << std::endl
        << "   12                   " << std::endl
        << "    |                   " << std::endl
        << "   /                    " << std::endl
        << "11                      " << std::endl;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(TreeTests, PrintNullTreeTest)
{
    Tree<int> A;

    std::stringstream ss1;

    std::stringstream ss2;
    ss2 << A;
    ASSERT_EQ(ss1.str(), ss2.str());
}
