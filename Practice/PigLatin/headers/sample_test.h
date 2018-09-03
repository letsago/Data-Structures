#ifndef __TESTS_H__
#define __TESTS_H__

#include "test_helpers.h"

class SampleUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(SampleUnitTests::CompareTest);
        ADD_TEST(SampleUnitTests::NullTest);
        ADD_TEST(SampleUnitTests::InvalidSymbolTest);
        ADD_TEST(SampleUnitTests::WordTest);
        // ADD_TEST(SampleUnitTests::AppropriateSpacingTest);
        ADD_TEST(SampleUnitTests::SentenceTest);
        ADD_TEST(SampleUnitTests::MultiplePunctuationTest);
    }

private:
    static bool CompareTest();
    static bool NullTest();
    static bool InvalidSymbolTest();
    static bool WordTest();
    // static bool AppropriateSpacingTest();
    static bool SentenceTest();
    static bool MultiplePunctuationTest();

    static Test_Registrar<SampleUnitTests> registrar;
};

#endif 