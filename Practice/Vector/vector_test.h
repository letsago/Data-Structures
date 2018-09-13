#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <pyu/vector.h>

class VectorTests final : public LinearStorageInterfaceTests
{
protected:
    pyu::LinearStorageInterface<int>* createTestLSI()
    {
        return new pyu::Vector<int>();
    }

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(VectorTests::ResizeTest);
        ADD_TEST(VectorTests::CopyTest);
        ADD_TEST(VectorTests::AssignmentTest);
    }

private:
    bool ResizeTest();
    bool AssignmentTest();
    bool CopyTest();

    static Test_Registrar<VectorTests> registrar;
}; 
