#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <pyu/linked_list.h>
#include <pyu/shared_ptr.h>

class LinkedListTests final : public LinearStorageInterfaceTests
{
protected:
    pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI()
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::LinkedList<int>());
    }

    pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI(pyu::shared_ptr<pyu::LinearStorageInterface<int>>& other)
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::LinkedList<int>(dynamic_cast<pyu::LinkedList<int>&>(*other)));
    }

    void RunTests() final
    {
        LinearStorageInterfaceTests::RunTests();
        ADD_TEST(LinkedListTests::FindManyTest);
    }

private:
    bool FindManyTest();

    static Test_Registrar<LinkedListTests> registrar;
};
