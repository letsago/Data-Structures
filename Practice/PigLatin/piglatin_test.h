#pragma once

#include <pyu/test_lib.h>

class PigLatinTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(CompareTest);
        ADD_TEST(NullTest);
        ADD_TEST(InvalidSymbolTest);
        ADD_TEST(WordTest);
        ADD_TEST(SentenceTest);
        ADD_TEST(MultiplePunctuationTest);
        ADD_TEST(MultipleSpacesTest);
    }

private:
    bool CompareTest();
    bool NullTest();
    bool InvalidSymbolTest();
    bool WordTest();
    bool SentenceTest();
    bool MultiplePunctuationTest();
    bool MultipleSpacesTest();

    static Test_Registrar<PigLatinTests> registrar;
}; 