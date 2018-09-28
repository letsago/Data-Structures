#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <pyu/array.h>
#include <pyu/shared_ptr.h>

class ArrayTests final : public LinearStorageInterfaceTests
{
protected:
    pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI()
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 10>());
    }
    pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI(pyu::shared_ptr<pyu::LinearStorageInterface<int>>& other)
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 10>(dynamic_cast<pyu::Array<int, 10>&>(*other)));
    }

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(StaticMemoryTest);
    }

private:
    bool StaticMemoryTest();

    static Test_Registrar<ArrayTests> registrar;
};
