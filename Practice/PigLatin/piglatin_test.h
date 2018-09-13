#pragma once

#include <pyu/test_lib.h>

class PigLatinTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(PigLatinTests::CompareTest);
        ADD_TEST(PigLatinTests::NullTest);
        ADD_TEST(PigLatinTests::InvalidSymbolTest);
        ADD_TEST(PigLatinTests::WordTest);
        ADD_TEST(PigLatinTests::SentenceTest);
        ADD_TEST(PigLatinTests::MultiplePunctuationTest);
        ADD_TEST(PigLatinTests::MultipleSpacesTest);
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