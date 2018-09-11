#pragma once

#include <pyu/test_lib.h>

class PigLatinTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(PigLatinTests::ResizeTest);
        ADD_TEST(PigLatinTests::AssignmentOverloadTest);
        ADD_TEST(PigLatinTests::CopyTest);
        ADD_TEST(PigLatinTests::InsertTest);
        ADD_TEST(PigLatinTests::RemoveTest);
        ADD_TEST(PigLatinTests::CompareTest);
        ADD_TEST(PigLatinTests::NullTest);
        ADD_TEST(PigLatinTests::InvalidSymbolTest);
        ADD_TEST(PigLatinTests::WordTest);
        ADD_TEST(PigLatinTests::SentenceTest);
        ADD_TEST(PigLatinTests::MultiplePunctuationTest);
        ADD_TEST(PigLatinTests::MultipleSpacesTest);
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

    static Test_Registrar<PigLatinTests> registrar;
}; 