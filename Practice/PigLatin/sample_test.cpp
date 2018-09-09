#include "headers/sample_test.h"
#include "headers/piglatin.h"

Test_Registrar<SampleUnitTests> SampleUnitTests::registrar;

bool compare(const MyVector<char>& input, const char* output)
{
    int index = 0;
    do
    {
        if (input.At(index) != output[index])
            return false;       

    } while(output[index++] != '\0');

    return true;
}

bool SampleUnitTests::CompareTest()
{
    const char str[] = "hiya";
    MyVector<char> A(str, sizeof(str));
    VERIFY_EQ(sizeof(str), 5);
    VERIFY_FALSE(compare(A, "h"));
    VERIFY_TRUE(compare(A, "hiya"));
    VERIFY_FALSE(compare(A, "hiyaa"));

    return true;
}

bool SampleUnitTests::NullTest()
{
    MyVector<char> A;
    MyVector<char> B;
    VERIFY_FALSE(pigLatinTranslate(A, B));

    return true;
}

bool SampleUnitTests::InvalidSymbolTest()
{
    int counter = 0; // will keep track of all possible number of invalid chars
    for (int i = 0; i < 256; ++i)
    {
        char sym[] = {static_cast<char>(i)};
        MyVector<char> A(sym, sizeof(sym));
        if (doInvalidCharsExist(A))
            ++counter;
    }

    VERIFY_EQ(counter, 196); // counter = num of invalid chars, therefore num of valid chars = 60

    const char str[] = "hi:)";
    MyVector<char> A(str, sizeof(str));
    VERIFY_TRUE(doInvalidCharsExist(A));

    const char str2[] = "I like pie.";
    MyVector<char> B(str2, sizeof(str2));
    VERIFY_FALSE(doInvalidCharsExist(B));

    return true;
}

bool SampleUnitTests::WordTest()
{
    const char str[] = "hello";
    MyVector<char> A(str, sizeof(str));
    MyVector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "ellohay"));

    const char str1[] = "x-ray";
    MyVector<char> C(str1, sizeof(str1));
    MyVector<char> D;
    VERIFY_TRUE(pigLatinTranslate(C, D));
    VERIFY_TRUE(compare(D, "-rayxay"));

    const char str2[] = "i'll";
    MyVector<char> E(str2, sizeof(str2));
    MyVector<char> F;
    VERIFY_TRUE(pigLatinTranslate(E, F));
    VERIFY_TRUE(compare(F, "i'llyay"));

    return true;
}

bool SampleUnitTests::SentenceTest()
{
    const char str[] = "I like pie.";
    MyVector<char> A(str, sizeof(str));
    MyVector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Iyay ikelay iepay."));
    
    return true;
}

bool SampleUnitTests::MultiplePunctuationTest()
{
    const char str[] = "Oh My snot!!! how come??";
    MyVector<char> A(str, sizeof(str));
    MyVector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Ohyay Ymay otsnay!!! owhay omecay??"));

    return true;
}

bool SampleUnitTests::MultipleSpacesTest()
{
    const char str[] = "I like   pie.";
    MyVector<char> A(str, sizeof(str));
    MyVector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Iyay ikelay iepay."));

    return true;
}

bool SampleUnitTests::ResizeTest()
{
    const int arr[] = {8, 8, 8};
    MyVector<int> A(arr, sizeof(arr)/sizeof(arr[0]));
    VERIFY_EQ(A.Capacity(), 3);
    VERIFY_EQ(A.Length(), 3);

    A.Resize(9);
    VERIFY_EQ(A.Capacity(), 9);
    VERIFY_EQ(A.Length(), 3);

    A.Insert_front(2);
    VERIFY_EQ(A.Capacity(), 9);
    VERIFY_EQ(A.Length(), 4);

    A.Remove_back();
    VERIFY_EQ(A.Capacity(), 9);
    VERIFY_EQ(A.Length(), 3);

    A.Resize(6);
    VERIFY_EQ(A.Capacity(), 6);
    VERIFY_EQ(A.Length(), 3);

    const int arr2[10] = {0};
    MyVector<int> B(arr2, sizeof(arr2)/sizeof(arr2[0]));
    VERIFY_EQ(B.Capacity(), 10);
    VERIFY_EQ(B.Length(), 10);

    B.Resize(5);
    VERIFY_EQ(B.Capacity(), 5);
    VERIFY_EQ(B.Length(), 5);

    B.Insert_front(3);
    VERIFY_EQ(B.Capacity(), 10);
    VERIFY_EQ(B.Length(), 6);

    B.Remove_back();
    VERIFY_EQ(B.Capacity(), 10);
    VERIFY_EQ(B.Length(), 5);

    MyVector<int> C;
    VERIFY_EQ(C.Capacity(), 0);
    VERIFY_EQ(C.Length(), 0);

    C.Insert_front(8);
    VERIFY_EQ(C.Capacity(), 1);
    VERIFY_EQ(C.Length(), 1);

    C.Insert_front(2);
    VERIFY_EQ(C.Capacity(), 2);
    VERIFY_EQ(C.Length(), 2);

    C.Insert_back(6);
    VERIFY_EQ(C.Capacity(), 4);
    VERIFY_EQ(C.Length(), 3);

    C.Clear();
    VERIFY_EQ(C.Capacity(), 0);
    VERIFY_EQ(C.Length(), 0);

    return true;
}

bool SampleUnitTests::InsertTest()
{
    MyVector<int> A;
    VERIFY_TRUE(A.Insert_front(1));
    VERIFY_TRUE(A.Insert(1, 2));
    VERIFY_TRUE(A.Insert_back(3));

    for (int i = 0; i < A.Length(); ++i)
    {
        VERIFY_EQ(A.At(i), i + 1);
    }
    
    const int arr[] = {4, 5, 6};
    MyVector<int> B(arr, sizeof(arr)/sizeof(arr[0]));
    VERIFY_FALSE(A.Insert(4, 8));
    VERIFY_TRUE(A.Insert(3, 7));
    VERIFY_EQ(A.At(3), 7);

    return true;
}

bool SampleUnitTests::RemoveTest()
{
    MyVector <int> B;
    VERIFY_FALSE(B.Remove_back());
    VERIFY_FALSE(B.Remove_front());
    VERIFY_FALSE(B.Remove(0));

    const int arr[] = {1, 2, 3, 4};
    MyVector<int> A(arr, sizeof(arr)/sizeof(arr[0]));
    VERIFY_FALSE(A.Remove(4));
    VERIFY_TRUE(A.Remove(2));
    VERIFY_EQ(A.Front(), 1);
    VERIFY_EQ(A.At(1), 2);
    VERIFY_EQ(A.At(2), 4);
    VERIFY_TRUE(A.Remove_back());
    VERIFY_EQ(A.Back(), 2);
    VERIFY_TRUE(A.Remove_front());
    VERIFY_EQ(A.Front(), 2);
    VERIFY_EQ(A.Back(), 2);

    return true;
}

bool SampleUnitTests::AssignmentOverloadTest()
{
    const int arr[] = {1, 2, 3, 4, 5};
    MyVector<int> A(arr, sizeof(arr)/sizeof(arr[0]));

    MyVector<int> B;
    VERIFY_EQ(B.Capacity(), 0);
    VERIFY_EQ(B.Length(), 0);
    VERIFY_TRUE(B.Empty());

    B = A;
    VERIFY_EQ(B.Capacity(), 5);
    VERIFY_EQ(B.Length(), 5);

    for (int i = 0; i < B.Length(); ++i)
    {
        VERIFY_EQ(B.At(i), i + 1);
    }

    MyVector<int> C;
    B = C;
    VERIFY_TRUE(B.Empty());
    VERIFY_EQ(B.Capacity(), 0);
    VERIFY_EQ(B.Length(), 0);

    B.Resize(10);
    C = B;
    VERIFY_EQ(C.Capacity(), 10);
    VERIFY_EQ(C.Length(), 0);
    
    return true;
}

bool SampleUnitTests::CopyTest()
{
    const int arr[] = {1, 2, 3, 4, 5};
    MyVector<int> A(arr, sizeof(arr)/sizeof(arr[0]));

    MyVector<int> B(A);
    VERIFY_EQ(B.Capacity(), 5);
    VERIFY_EQ(B.Length(), 5);

    for (int i = 0; i < B.Length(); ++i)
    {
        VERIFY_EQ(B.At(i), i + 1);
    }

    MyVector<int> C;
    MyVector<int> D(C);
    VERIFY_TRUE(D.Empty());
    VERIFY_EQ(D.Capacity(), 0);
    VERIFY_EQ(D.Length(), 0);

    C.Resize(10);
    MyVector<int> E(C);
    VERIFY_EQ(E.Capacity(), 10);
    VERIFY_EQ(E.Length(), 0);

    return true;
}