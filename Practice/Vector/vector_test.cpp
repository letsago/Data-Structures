#include "vector_test.h"
#include <pyu/vector.h>

using namespace pyu;

Test_Registrar<VectorTests> VectorTests::registrar;

bool VectorTests::ResizeTest()
{
    const int arr[] = {8, 8, 8};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));
    VERIFY_EQ(A.capacity(), 3);
    VERIFY_EQ(A.length(), 3);

    A.resize(9);
    VERIFY_EQ(A.capacity(), 9);
    VERIFY_EQ(A.length(), 3);

    A.insert_front(2);
    VERIFY_EQ(A.capacity(), 9);
    VERIFY_EQ(A.length(), 4);

    A.remove_back();
    VERIFY_EQ(A.capacity(), 9);
    VERIFY_EQ(A.length(), 3);

    A.resize(6);
    VERIFY_EQ(A.capacity(), 6);
    VERIFY_EQ(A.length(), 3);

    const int arr2[10] = {0};
    Vector<int> B(arr2, sizeof(arr2)/sizeof(arr2[0]));
    VERIFY_EQ(B.capacity(), 10);
    VERIFY_EQ(B.length(), 10);

    B.resize(5);
    VERIFY_EQ(B.capacity(), 5);
    VERIFY_EQ(B.length(), 5);

    B.insert_front(3);
    VERIFY_EQ(B.capacity(), 10);
    VERIFY_EQ(B.length(), 6);

    B.remove_back();
    VERIFY_EQ(B.capacity(), 10);
    VERIFY_EQ(B.length(), 5);

    Vector<int> C;
    VERIFY_EQ(C.capacity(), 0);
    VERIFY_EQ(C.length(), 0);

    C.insert_front(8);
    VERIFY_EQ(C.capacity(), 1);
    VERIFY_EQ(C.length(), 1);

    C.insert_front(2);
    VERIFY_EQ(C.capacity(), 2);
    VERIFY_EQ(C.length(), 2);

    C.insert_back(6);
    VERIFY_EQ(C.capacity(), 4);
    VERIFY_EQ(C.length(), 3);

    C.clear();
    VERIFY_EQ(C.capacity(), 0);
    VERIFY_EQ(C.length(), 0);

    return true;
}

bool VectorTests::AssignmentTest()
{
    const int arr[] = {1, 2, 3, 4, 5};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));

    Vector<int> B;
    VERIFY_EQ(B.capacity(), 0);
    VERIFY_EQ(B.length(), 0);
    VERIFY_TRUE(B.empty());

    B = A;
    VERIFY_EQ(B.capacity(), 5);
    VERIFY_EQ(B.length(), 5);

    for (uint32_t i = 0; i < B.length(); ++i)
    {
        VERIFY_EQ(B.at(i), i + 1);
    }

    Vector<int> C;
    B = C;
    VERIFY_TRUE(B.empty());
    VERIFY_EQ(B.capacity(), 0);
    VERIFY_EQ(B.length(), 0);

    B.resize(10);
    C = B;
    VERIFY_EQ(C.capacity(), 10);
    VERIFY_EQ(C.length(), 0);
    
    return true;
}

bool VectorTests::CopyTest()
{
    const int arr[] = {1, 2, 3, 4, 5};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));

    Vector<int> B(A);
    VERIFY_EQ(B.capacity(), 5);
    VERIFY_EQ(B.length(), 5);

    for (uint32_t i = 0; i < B.length(); ++i)
    {
        VERIFY_EQ(B.at(i), i + 1);
    }

    Vector<int> C;
    Vector<int> D(C);
    VERIFY_TRUE(D.empty());
    VERIFY_EQ(D.capacity(), 0);
    VERIFY_EQ(D.length(), 0);

    C.resize(10);
    Vector<int> E(C);
    VERIFY_EQ(E.capacity(), 10);
    VERIFY_EQ(E.length(), 0);

    return true;
}