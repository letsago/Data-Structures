#pragma once

#include <pyu/test_lib.h>

class StackTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(StackTests::PushTest);
        ADD_TEST(StackTests::PopTest);
        ADD_TEST(StackTests::TopTest);
        ADD_TEST(StackTests::AssignmentTest);
        ADD_TEST(StackTests::CopyTest);
        ADD_TEST(StackTests::ClearTest);
    }

private:
    static bool PushTest();
    static bool PopTest();
    static bool TopTest();
    static bool AssignmentTest();
    static bool CopyTest();
    static bool ClearTest();

    static Test_Registrar<StackTests> registrar;
};