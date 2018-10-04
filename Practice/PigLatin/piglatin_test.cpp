#include "piglatin_test.h"

TEST_F(PigLatinTests, NullTest)
{
    pyu::Vector<char> A;
    pyu::Vector<char> B;
    ASSERT_FALSE(pigLatinTranslate(A, B));
}

TEST_F(PigLatinTests, InvalidSymbolTest)
{
    int counter = 0; // will keep track of all possible number of invalid chars
    for (uint32_t i = 0; i < 256; ++i)
    {
        char sym[] = {static_cast<char>(i)};
        pyu::Vector<char> A(sym, sizeof(sym));
        if (doInvalidCharsExist(A))
            ++counter;
    }

    ASSERT_EQ(counter, 196); // counter = num of invalid chars, therefore num of valid chars = 60

    const char str[] = "hi:)";
    pyu::Vector<char> A(str, sizeof(str));
    ASSERT_TRUE(doInvalidCharsExist(A));

    const char str2[] = "I like pie.";
    pyu::Vector<char> B(str2, sizeof(str2));
    ASSERT_FALSE(doInvalidCharsExist(B));
}

TEST_F(PigLatinTests, WordTest)
{
    const char str[] = "hello";
    pigLatinTester(str, sizeof(str), "ellohay");

    const char str1[] = "x-ray";
    pigLatinTester(str1, sizeof(str1), "-rayxay");

    const char str2[] = "i'll";
    pigLatinTester(str2, sizeof(str2), "i'llyay");
}

TEST_F(PigLatinTests, SentenceTest)
{
    const char str[] = "I like pie.";
    pigLatinTester(str, sizeof(str), "Iyay ikelay iepay.");
}

TEST_F(PigLatinTests, MultiplePunctuationTest)
{
    const char str[] = "Oh My snot!!! how come??";
    pigLatinTester(str, sizeof(str), "Ohyay Ymay otsnay!!! owhay omecay??");
}

TEST_F(PigLatinTests, MultipleSpacesTest)
{
    const char str[] = "I like   pie.";
    pigLatinTester(str, sizeof(str), "Iyay ikelay iepay.");
}
