#ifndef __TESTS_H__
#define __TESTS_H__

#include "test_helpers.h"

class StackVectorTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(StackVectorTests::PushTest);
        ADD_TEST(StackVectorTests::PopTest);
        ADD_TEST(StackVectorTests::TopTest);
        ADD_TEST(StackVectorTests::AssignmentTest);
        ADD_TEST(StackVectorTests::CopyTest);
        ADD_TEST(StackVectorTests::ClearTest);
    }

private:
    static bool PushTest();
    static bool PopTest();
    static bool TopTest();
    static bool AssignmentTest();
    static bool CopyTest();
    static bool ClearTest();

    static Test_Registrar<StackVectorTests> registrar;
};

#endif 