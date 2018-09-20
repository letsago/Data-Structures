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

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(ResizeTest);
        ADD_TEST(CopyTest);
        ADD_TEST(AssignmentTest);
    }

private:
    bool ResizeTest();
    bool AssignmentTest();
    bool CopyTest();

    static Test_Registrar<VectorTests> registrar;
}; 
