#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <pyu/vector.h>
#include <pyu/shared_ptr.h>

class VectorTests final : public LinearStorageInterfaceTests
{
protected:
    pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI()
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Vector<int>());
    }

    pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI(pyu::shared_ptr<pyu::LinearStorageInterface<int>>& other)
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Vector<int>(dynamic_cast<pyu::Vector<int>&>(*other)));
    }

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(ResizeTest);
    }

private:
    bool ResizeTest();

    static Test_Registrar<VectorTests> registrar;
};
