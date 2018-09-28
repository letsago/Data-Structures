#include "tree_test.h"
#include <pyu/tree.h>
#include <pyu/vector.h>

using namespace pyu;

Test_Registrar<TreeTests> TreeTests::registrar;

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
