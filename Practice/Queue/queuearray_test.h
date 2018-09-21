#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/rollingarray.h>
#include <pyu/shared_ptr.h>

class QueueArrayTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(InvalidPushTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::RollingArray<int, 5>));
        ADD_TEST(RollingPopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::RollingArray<int, 5>));
    }

private:
    bool InvalidPushTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);
    bool RollingPopTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);

    static Test_Registrar<QueueArrayTests> registrar;
};