#include "headers/sample_test.h"
#include "headers/myvector_class.h"

Test_Registrar<SampleUnitTests> SampleUnitTests::registrar;

bool SampleUnitTests::InsertTest()
{
    // tests whether or not insert() can actually be performed
    MyVector<int> A(1, 6);
    VERIFY_FALSE(A.Insert(-10, 10));
    VERIFY_TRUE(A.Insert(0, 10));

    // tests insertion when position is less than memory size
    A.Insert(3, 10);
    VERIFY_EQ(A.At(3), 10);
    VERIFY_EQ(A.At(1), 6);
    VERIFY_EQ(A.At(2), 0);

    // tests insertion when position exceeds memory size
    A.Insert(10, 2);
    VERIFY_EQ(A.At(9), 0);

    // tests insert_back function
    A.Insert_back(4);
    VERIFY_EQ(A.Back(), 4);

    // tests insert_front function
    A.Insert_front(12);
    VERIFY_EQ(A.Front(), 12);

    return true;
}

bool SampleUnitTests::RemoveTest()
{
    // tests whether or not remove() can be performed
    MyVector<int> A(5, 6);
    VERIFY_FALSE(A.Remove(-1));
    VERIFY_FALSE(A.Remove(5));

    // tests remove() after insertion
    A.Insert(3, 2);
    A.Remove(2);
    VERIFY_EQ(A.At(2), 2);

    // tests remove_back()
    A.Remove_back();
    VERIFY_EQ(A.Back(), 6);

    // tests remove_front()
    A.Remove_front();
    A.Remove_front();
    VERIFY_EQ(A.Front(), 2);

    return true;
}

bool SampleUnitTests::EmptyTest()
{
    MyVector<int> A;

    // tests if array is empty
    VERIFY_TRUE(A.Empty());

    MyVector<int> B(8, 8);

    // tests if array is not empty 
    VERIFY_FALSE(B.Empty());
    
    B.Clear();

    // tests if Clear() function empties array
    VERIFY_TRUE(B.Empty());

    return true;
}