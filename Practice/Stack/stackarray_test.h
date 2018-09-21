#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/array.h>
#include <pyu/shared_ptr.h>

class StackArrayTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(InvalidPushTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 5>));
    }

private:
    bool InvalidPushTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);

    static Test_Registrar<StackArrayTests> registrar;
};