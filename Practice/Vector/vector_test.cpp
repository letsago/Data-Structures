#include <gtest/gtest.h>
#include <pyu/vector.h>

TEST(VectorTests, ResizeTest)
{
    const int arr[] = {8, 8, 8};
    pyu::Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));
    ASSERT_EQ(A.capacity(), 3);
    ASSERT_EQ(A.length(), 3);

    A.resize(9);
    ASSERT_EQ(A.capacity(), 9);
    ASSERT_EQ(A.length(), 3);

    A.insert_front(2);
    ASSERT_EQ(A.capacity(), 9);
    ASSERT_EQ(A.length(), 4);

    A.remove_back();
    ASSERT_EQ(A.capacity(), 9);
    ASSERT_EQ(A.length(), 3);

    A.resize(6);
    ASSERT_EQ(A.capacity(), 6);
    ASSERT_EQ(A.length(), 3);

    const int arr2[10] = {0};
    pyu::Vector<int> B(arr2, sizeof(arr2)/sizeof(arr2[0]));
    ASSERT_EQ(B.capacity(), 10);
    ASSERT_EQ(B.length(), 10);

    B.resize(5);
    ASSERT_EQ(B.capacity(), 5);
    ASSERT_EQ(B.length(), 5);

    B.insert_front(3);
    ASSERT_EQ(B.capacity(), 10);
    ASSERT_EQ(B.length(), 6);

    B.remove_back();
    ASSERT_EQ(B.capacity(), 10);
    ASSERT_EQ(B.length(), 5);

    pyu::Vector<int> C;
    ASSERT_EQ(C.capacity(), 0);
    ASSERT_EQ(C.length(), 0);

    C.insert_front(8);
    ASSERT_EQ(C.capacity(), 1);
    ASSERT_EQ(C.length(), 1);

    C.insert_front(2);
    ASSERT_EQ(C.capacity(), 2);
    ASSERT_EQ(C.length(), 2);

    C.insert_back(6);
    ASSERT_EQ(C.capacity(), 4);
    ASSERT_EQ(C.length(), 3);

    C.clear();
    ASSERT_EQ(C.capacity(), 0);
    ASSERT_EQ(C.length(), 0);
}
