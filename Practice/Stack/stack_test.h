#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/vector.h>
#include <pyu/linked_list.h>
#include <pyu/array.h>
#include <pyu/shared_ptr.h>

class StackTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(PushTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Vector<int>));
        ADD_TEST(PushTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::LinkedList<int>));
        ADD_TEST(PushTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 10>));
        ADD_TEST(PopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Vector<int>));
        ADD_TEST(PopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::LinkedList<int>));
        ADD_TEST(PopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 10>));
        ADD_TEST(TopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Vector<int>));
        ADD_TEST(TopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::LinkedList<int>));
        ADD_TEST(TopTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 10>));
        ADD_TEST(ClearTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Vector<int>));
        ADD_TEST(ClearTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::LinkedList<int>));
        ADD_TEST(ClearTest, pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new pyu::Array<int, 10>));
    }

private:
    bool PushTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);
    bool PopTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);
    bool TopTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);
    bool ClearTest(pyu::shared_ptr<pyu::LinearStorageInterface<int>> pLsi);

    static Test_Registrar<StackTests> registrar;
};