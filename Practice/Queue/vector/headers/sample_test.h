#ifndef __TESTS_H__
#define __TESTS_H__

#include "test_helpers.h"

class QueueVectorTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(QueueVectorTests::PushTest);
        ADD_TEST(QueueVectorTests::PopTest);
        ADD_TEST(QueueVectorTests::FrontTest);
        ADD_TEST(QueueVectorTests::AssignmentTest);
        ADD_TEST(QueueVectorTests::CopyTest);
        ADD_TEST(QueueVectorTests::ClearTest);
    }

private:
    static bool PushTest();
    static bool PopTest();
    static bool FrontTest();
    static bool AssignmentTest();
    static bool CopyTest();
    static bool ClearTest();

    static Test_Registrar<QueueVectorTests> registrar;
};

#endif 