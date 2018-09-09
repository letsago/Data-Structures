#ifndef __TESTS_H__
#define __TESTS_H__

#include "test_helpers.h"

class SampleUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(SampleUnitTests::ResizeTest);
        ADD_TEST(SampleUnitTests::AssignmentOverloadTest);
        ADD_TEST(SampleUnitTests::CopyTest);
        ADD_TEST(SampleUnitTests::InsertTest);
        ADD_TEST(SampleUnitTests::RemoveTest);
        ADD_TEST(SampleUnitTests::CompareTest);
        ADD_TEST(SampleUnitTests::NullTest);
        ADD_TEST(SampleUnitTests::InvalidSymbolTest);
        ADD_TEST(SampleUnitTests::WordTest);
        ADD_TEST(SampleUnitTests::SentenceTest);
        ADD_TEST(SampleUnitTests::MultiplePunctuationTest);
        ADD_TEST(SampleUnitTests::MultipleSpacesTest);
    }

private:
    static bool ResizeTest();
    static bool AssignmentOverloadTest();
    static bool CopyTest();
    static bool InsertTest();
    static bool RemoveTest();
    static bool CompareTest();
    static bool NullTest();
    static bool InvalidSymbolTest();
    static bool WordTest();
    static bool SentenceTest();
    static bool MultiplePunctuationTest();
    static bool MultipleSpacesTest();

    static Test_Registrar<SampleUnitTests> registrar;
};

#endif 