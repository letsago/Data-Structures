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

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(StaticMemoryTest);
        ADD_TEST(AssignmentTest);
        ADD_TEST(CopyTest);
    }

private:
    bool StaticMemoryTest();
    bool AssignmentTest();
    bool CopyTest();

    static Test_Registrar<ArrayTests> registrar;
}; 
