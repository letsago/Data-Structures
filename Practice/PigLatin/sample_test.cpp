#include "headers/sample_test.h"
#include "headers/piglatin.h"

Test_Registrar<SampleUnitTests> SampleUnitTests::registrar;

bool compare(const MyVector<char>& input, const char* output)
{
    // for both input and output, loop until '\0' character, calculate sizes and then iterate over sizes
    int output_length = 0;
    
    while (output[output_length] != '\0')
    {
        ++output_length;
    }

    if ((input.Length() - 1) != output_length)
    {
        return false;
    }

    for (int i = 0; i < output_length; ++i)
    {
        if (input.Data()[i] != output[i])
            return false;
    }

    return true;
}

bool SampleUnitTests::CompareTest()
{
    const char str[] = "hiya";
    MyVector<char> A(str, sizeof(str));
    VERIFY_TRUE(compare(A, str));
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

// bool SampleUnitTests::AppropriateSpacingTest()
// {
//     const char str1[] = "hi!hello?";
//     MyVector<char> A(str1, sizeof(str1));
//     MyVector<char> B;
//     appropriatelySpace(A, B);
//     VERIFY_TRUE(compare(B, "hi! hello?"));

//     const char str2[] = "Yippy!  I feel great!";
//     MyVector<char> C(str2, sizeof(str2));
//     MyVector<char> D;
//     appropriatelySpace(C, D);
//     VERIFY_TRUE(compare(D, "Yippy! I feel great!"));

//     const char str3[] = " Hi! ";
//     MyVector<char> E(str3, sizeof(str3));
//     MyVector<char> F;
//     appropriatelySpace(E, F);
//     VERIFY_TRUE(compare(F, "Hi!"));

//     return true;
// }

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
    MyVector<char> A("Oh My snot!!! how come??", 25);
    MyVector<char> B;
    VERIFY_TRUE(pigLatinTranslate(A, B));
    VERIFY_TRUE(compare(B, "Ohyay Ymay otsnay!!! owhay omecay??"));
    return true;
}
