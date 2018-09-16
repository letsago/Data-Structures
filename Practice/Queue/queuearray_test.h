#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/rollingarray.h>

class QueueArrayTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(QueueArrayTests::InvalidPushTest, new pyu::RollingArray<int, 5>);
        ADD_TEST(QueueArrayTests::RollingPopTest, new pyu::RollingArray<int, 5>);
    }

private:
    bool InvalidPushTest(pyu::LinearStorageInterface<int>* pLsi);
    bool RollingPopTest(pyu::LinearStorageInterface<int>* pLsi);

    static Test_Registrar<QueueArrayTests> registrar;
};