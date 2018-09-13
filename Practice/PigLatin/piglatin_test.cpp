#include "piglatin_test.h"
#include "piglatin.h"

using namespace pyu;

Test_Registrar<PigLatinTests> PigLatinTests::registrar;

bool compare(const Vector<char>& input, const char* output)
{
    int index = 0;
    do
    {
        if (input.at(index) != output[index])
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
    for (uint32_t i = 0; i < 256; ++i)
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