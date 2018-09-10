#ifndef __TESTS_H__
#define __TESTS_H__

#include "test_helpers.h"

class SampleUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(SampleUnitTests::InsertTest);
        ADD_TEST(SampleUnitTests::RemoveTest);
        ADD_TEST(SampleUnitTests::InsertFrontTest);
        ADD_TEST(SampleUnitTests::InsertBackTest);
        ADD_TEST(SampleUnitTests::RemoveFrontTest);
        ADD_TEST(SampleUnitTests::RemoveBackTest);
        ADD_TEST(SampleUnitTests::FindFirstTest);
        ADD_TEST(SampleUnitTests::FindManyTest);
        ADD_TEST(SampleUnitTests::ClearTest);
        ADD_TEST(SampleUnitTests::AssignmentOperatorTest);
        ADD_TEST(SampleUnitTests::CopyTest);
        ADD_TEST(SampleUnitTests::AtTest);
    }

private:
    static bool InsertTest();
    static bool RemoveTest();
    static bool InsertFrontTest();
    static bool InsertBackTest();
    static bool RemoveFrontTest();
    static bool RemoveBackTest();
    static bool FindFirstTest();
    static bool FindManyTest();
    static bool ClearTest();
    static bool AssignmentOperatorTest();
    static bool CopyTest();
    static bool AtTest();

    static Test_Registrar<SampleUnitTests> registrar;
};

#endif 