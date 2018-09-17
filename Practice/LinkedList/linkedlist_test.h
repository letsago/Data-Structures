#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <pyu/linked_list.h>

class LinkedListTests final : public LinearStorageInterfaceTests
{
protected:
    pyu::LinearStorageInterface<int>* createTestLSI()
    {
        return new pyu::LinkedList<int>();
    }

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(FindManyTest);
        ADD_TEST(CopyTest);
        ADD_TEST(AssignmentTest);
    }

private:
    bool FindManyTest();
    bool AssignmentTest();
    bool CopyTest();

    static Test_Registrar<LinkedListTests> registrar;
};
