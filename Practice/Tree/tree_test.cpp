#include "tree_test.h"
#include <pyu/tree.h>
#include <pyu/vector.h>
#include <iostream>
#include <sstream>

using namespace pyu;

Test_Registrar<TreeTests> TreeTests::registrar;

bool IsSorted(const Tree<int>& other, const Vector<int>& sorted)
{
    if (other.size() != sorted.length())
        return false;

    for (uint32_t i = 0; i < sorted.length(); ++i)
    {
        if (!other.contains(sorted.at(i)))
            return false;

        if (i != 0)
        {
            if (sorted.at(i) <= sorted.at(i - 1))
                return false;
        }
    }

    return true;
}

bool TreeTests::InsertTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.insert(data.at(i)));
    }

    VERIFY_EQ(A.size(), data.length());

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.contains(data.at(i)));
    }

    VERIFY_FALSE(A.insert(10));
    VERIFY_FALSE(A.insert(8));
    VERIFY_FALSE(A.insert(2));

    return true;
}

bool TreeTests::RemoveRootTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    VERIFY_FALSE(A.remove(8));

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.insert(data.at(i)));
    }

    VERIFY_EQ(A.size(), data.length());

    // tests for removing root
    VERIFY_TRUE(A.remove(10));
    data.remove(data.find(10));
    VERIFY_EQ(A.size(), data.length());

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.contains(data.at(i)));
    }

    VERIFY_FALSE(A.remove(10));

    // tests for another iteration of removing root
    VERIFY_TRUE(A.remove(5));
    data.remove(data.find(5));
    VERIFY_EQ(A.size(), data.length());

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.contains(data.at(i)));
    }

    return true;
}

bool TreeTests::RemoveLeafTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.insert(data.at(i)));
    }

    VERIFY_EQ(A.size(), 7);

    // removes a middle leaf
    VERIFY_TRUE(A.remove(5));
    data.remove(data.find(5));
    VERIFY_EQ(A.size(), data.length());

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.contains(data.at(i)));
    }

    // removes an end leaf
    VERIFY_TRUE(A.remove(15));
    data.remove(data.find(15));
    VERIFY_EQ(A.size(), data.length());

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.contains(data.at(i)));
    }

    return true;
}

bool TreeTests::ClearTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 1, 7, 9, 40, 30, 42, 28, 35, 26, 46, 50};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.insert(data.at(i)));
    }

    VERIFY_EQ(A.size(), data.length());

    A.clear();
    VERIFY_TRUE(A.empty());

    Tree<int> B;
    B.clear();
    VERIFY_TRUE(B.empty());

    return true;
}

bool TreeTests::ContainsTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 90, 34, -3, -10};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.insert(data.at(i)));
    }

    VERIFY_EQ(A.size(), data.length());

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.contains(data.at(i)));
    }

    VERIFY_FALSE(A.contains(100));
    VERIFY_FALSE(A.contains(0));
    VERIFY_FALSE(A.contains(-100));

    return true;
}

bool TreeTests::SortedBalancedTreeTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 12, 18};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        VERIFY_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return IsSorted(A, sorted);
}

bool TreeTests::SortedNonBalancedTreeTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 90, 34, -3, -10};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        VERIFY_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return IsSorted(A, sorted);
}

bool TreeTests::SortedRightSkewedTreeTest()
{
    const int arr[] = {10, 5, 20, 15, 25, 324, 90, 34};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        VERIFY_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return IsSorted(A, sorted);
}

bool TreeTests::SortedLeftSkewedTreeTest()
{
    const int arr[] = {10, 5, 20, 8, 2, 1, 3, -3, -10};

    Tree<int> A;

    for (uint32_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        VERIFY_TRUE(A.insert(arr[i]));
    }

    Vector<int> sorted = A.getSorted();

    return IsSorted(A, sorted);
}

bool TreeTests::SortedNullTreeTest()
{
    Tree<int> A;

    VERIFY_TRUE(A.getSorted().empty());

    return true;
}

bool TreeTests::DepthTest()
{
    const int arr[] = {10, 5, 20, 15, 8, 2, 25};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        VERIFY_TRUE(A.insert(data.at(i)));
    }

    VERIFY_EQ(A.depth(), 3);

    Tree<int> B;

    VERIFY_EQ(B.depth(), 0);

    const int arr2[] = {10, 5, 20, 15, 8, 2, 25, 23, 1, 3, 7, 324, 90, 34, -3, -10};
    Vector<int> data2(arr2, sizeof(arr2)/sizeof(arr2[0]));

    Tree<int> C;

    for (uint32_t i = 0; i < data2.length(); ++i)
    {
        VERIFY_TRUE(C.insert(data2.at(i)));
    }

    VERIFY_EQ(C.depth(), 6);

    return true;
}

bool TreeTests::PrintBalancedTreeTest()
{
    const int arr[] = {4, 2, 6, 1, 3, 5, 10};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1
        << "   4   "    << std::endl
        << " 2   6 "    << std::endl
        << "1 3 5 10"   << std::endl;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;
}

bool TreeTests::PrintNonBalancedTreeTest()
{
    const int arr[] = {10, 5, 20, 8, 2, 25, 1, 3, 7, 9, 30};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1
        << "       10       "   << std::endl
        << "   5       20   "   << std::endl
        << " 2   8       25 "   << std::endl
        << "1 3 7 9       30"   << std::endl;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;

}

bool TreeTests::PrintBigBalancedTreeTest()
{
    const int arr[] = {50, 25, 12, 38, 6, 3, 9, 18, 15, 22, 30, 26, 35, 42, 40, 48, 100, 75, 60, 55, 65, 85, 80, 90, 150, 175, 200, 160, 125, 108, 130};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1
        << "               50               "                   << std::endl
        << "       25               100       "                 << std::endl
        << "   12       38       75       150   "               << std::endl
        << " 6   18   30   42   60   85   125   175 "           << std::endl
        << "3 9 15 22 26 35 40 48 55 65 80 90 108 130 160 200"  << std::endl;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;
}

bool TreeTests::PrintBigNonBalancedTreeTest()
{
    const int arr[] = {28, 12, 6, 80, 43, 586, 100, 19, 29, 81, 25, 21, 34, 15};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1
        << "               28               "       << std::endl
        << "       12               80       "      << std::endl
        << "   6       19       43       586   "    << std::endl
        << "         15   25   29       100     "   << std::endl
        << "            21     34     81      "     << std::endl;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;
}

bool TreeTests::PrintRightSkewedTreeTest()
{
    const int arr[] = {11, 12, 13, 14};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1
        << "       11       "   << std::endl
        << "           12   "   << std::endl
        << "             13 "   << std::endl
        << "              14"   << std::endl;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;
}

bool TreeTests::PrintLeftSkewedTreeTest()
{
    const int arr[] = {14, 13, 12, 11};
    Vector<int> data(arr, sizeof(arr)/sizeof(arr[0]));

    Tree<int> A;

    for (uint32_t i = 0; i < data.length(); ++i)
    {
        A.insert(data.at(i));
    }

    std::stringstream ss1;
    ss1
        << "       14       "   << std::endl
        << "   13           "   << std::endl
        << " 12             "   << std::endl
        << "11              "   << std::endl;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;
}

bool TreeTests::PrintNullTreeTest()
{
    Tree<int> A;

    std::stringstream ss1;

    std::stringstream ss2;
    ss2 << A;
    VERIFY_EQ(ss1.str(), ss2.str());

    return true;
}
