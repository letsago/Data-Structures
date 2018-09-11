#include "piglatin_test.h"
#include "piglatin.h"

using namespace pyu;

Test_Registrar<PigLatinTests> PigLatinTests::registrar;

bool compare(const Vector<char>& input, const char* output)
{
    int index = 0;
    do
    {
        if (input.At(index) != output[index])
            return false;       

    } while(output[index++] != '\0');

    return true;
}

bool PigLatinTests::CompareTest()
{
    const char str[] = "hiya";
    Vector<char> A(str, sizeof(str));
    VERIFY_EQ(sizeof(str), 5);
    VERIFY_FALSE(compare(A, "h"));
    VERIFY_TRUE(compare(A, "hiya"));
    VERIFY_FALSE(compare(A, "hiyaa"));

    return true;
}

bool PigLatinTests::NullTest()
{
    Vector<char> A;
    Vector<char> B;
    VERIFY_FALSE(pigLatinTranslate(A, B));

    return true;
}

bool PigLatinTests::InvalidSymbolTest()
{
    int counter = 0; // will keep track of all possible number of invalid chars
    for (int i = 0; i < 256; ++i)
    {
        char sym[] = {static_cast<char>(i)};
        Vector<char> A(sym, sizeof(sym));
        if (doInvalidCharsExist(A))
            ++counter;
    }

    VERIFY_EQ(counter, 196); // counter = num of invalid chars, therefore num of valid chars = 60

    const char str[] = "hi:)";
    Vector<char> A(str, sizeof(str));
    VERIFY_TRUE(doInvalidCharsExist(A));

    const char str2[] = "I like pie.";
    Vector<char> B(str2, sizeof(str2));
    VERIFY_FALSE(doInvalidCharsExist(B));

    return true;
}

bool PigLatinTests::WordTest()
{
    const char str[] = "hello";
    Vector<char> A(str, sizeof(str));
    Vector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "ellohay"));

    const char str1[] = "x-ray";
    Vector<char> C(str1, sizeof(str1));
    Vector<char> D;
    VERIFY_TRUE(pigLatinTranslate(C, D));
    VERIFY_TRUE(compare(D, "-rayxay"));

    const char str2[] = "i'll";
    Vector<char> E(str2, sizeof(str2));
    Vector<char> F;
    VERIFY_TRUE(pigLatinTranslate(E, F));
    VERIFY_TRUE(compare(F, "i'llyay"));

    return true;
}

bool PigLatinTests::SentenceTest()
{
    const char str[] = "I like pie.";
    Vector<char> A(str, sizeof(str));
    Vector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Iyay ikelay iepay."));
    
    return true;
}

bool PigLatinTests::MultiplePunctuationTest()
{
    const char str[] = "Oh My snot!!! how come??";
    Vector<char> A(str, sizeof(str));
    Vector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Ohyay Ymay otsnay!!! owhay omecay??"));

    return true;
}

bool PigLatinTests::MultipleSpacesTest()
{
    const char str[] = "I like   pie.";
    Vector<char> A(str, sizeof(str));
    Vector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Iyay ikelay iepay."));

    return true;
}

bool PigLatinTests::ResizeTest()
{
    const int arr[] = {8, 8, 8};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));
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
    Vector<int> B(arr2, sizeof(arr2)/sizeof(arr2[0]));
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

    Vector<int> C;
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

bool PigLatinTests::InsertTest()
{
    Vector<int> A;
    VERIFY_TRUE(A.Insert_front(1));
    VERIFY_TRUE(A.Insert(1, 2));
    VERIFY_TRUE(A.Insert_back(3));

    for (int i = 0; i < A.Length(); ++i)
    {
        VERIFY_EQ(A.At(i), i + 1);
    }
    
    const int arr[] = {4, 5, 6};
    Vector<int> B(arr, sizeof(arr)/sizeof(arr[0]));
    VERIFY_FALSE(A.Insert(4, 8));
    VERIFY_TRUE(A.Insert(3, 7));
    VERIFY_EQ(A.At(3), 7);

    return true;
}

bool PigLatinTests::RemoveTest()
{
    Vector <int> B;
    VERIFY_FALSE(B.Remove_back());
    VERIFY_FALSE(B.Remove_front());
    VERIFY_FALSE(B.Remove(0));

    const int arr[] = {1, 2, 3, 4};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));
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

bool PigLatinTests::AssignmentOverloadTest()
{
    const int arr[] = {1, 2, 3, 4, 5};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));

    Vector<int> B;
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

    Vector<int> C;
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

bool PigLatinTests::CopyTest()
{
    const int arr[] = {1, 2, 3, 4, 5};
    Vector<int> A(arr, sizeof(arr)/sizeof(arr[0]));

    Vector<int> B(A);
    VERIFY_EQ(B.Capacity(), 5);
    VERIFY_EQ(B.Length(), 5);

    for (int i = 0; i < B.Length(); ++i)
    {
        VERIFY_EQ(B.At(i), i + 1);
    }

    Vector<int> C;
    Vector<int> D(C);
    VERIFY_TRUE(D.Empty());
    VERIFY_EQ(D.Capacity(), 0);
    VERIFY_EQ(D.Length(), 0);

    C.Resize(10);
    Vector<int> E(C);
    VERIFY_EQ(E.Capacity(), 10);
    VERIFY_EQ(E.Length(), 0);

    return true;
}