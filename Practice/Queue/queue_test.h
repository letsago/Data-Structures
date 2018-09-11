#pragma once

#include <pyu/test_lib.h>

class QueueTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(QueueTests::PushTest);
        ADD_TEST(QueueTests::PopTest);
        ADD_TEST(QueueTests::FrontTest);
        ADD_TEST(QueueTests::AssignmentTest);
        ADD_TEST(QueueTests::CopyTest);
        ADD_TEST(QueueTests::ClearTest);
    }

private:
    static bool PushTest();
    static bool PopTest();
    static bool FrontTest();
    static bool AssignmentTest();
    static bool CopyTest();
    static bool ClearTest();

    static Test_Registrar<QueueTests> registrar;
};