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
        ADD_TEST(SampleUnitTests::EmptyTest);
    }

private:
    static bool InsertTest();
    static bool RemoveTest();
    static bool EmptyTest();

    static Test_Registrar<SampleUnitTests> registrar;
};

#endif 