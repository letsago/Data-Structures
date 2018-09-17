#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/vector.h>
#include <pyu/linked_list.h>
#include <pyu/array.h>

class StackTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(PushTest, new pyu::Vector<int>);
        ADD_TEST(PushTest, new pyu::LinkedList<int>);
        ADD_TEST(PushTest, new pyu::Array<int, 10>);
        ADD_TEST(PopTest, new pyu::Vector<int>);
        ADD_TEST(PopTest, new pyu::LinkedList<int>);
        ADD_TEST(PopTest, new pyu::Array<int, 10>);
        ADD_TEST(TopTest, new pyu::Vector<int>);
        ADD_TEST(TopTest, new pyu::LinkedList<int>);
        ADD_TEST(TopTest, new pyu::Array<int, 10>);
        ADD_TEST(ClearTest, new pyu::Vector<int>);
        ADD_TEST(ClearTest, new pyu::LinkedList<int>);
        ADD_TEST(ClearTest, new pyu::Array<int, 10>);
    }

private:
    bool PushTest(pyu::LinearStorageInterface<int>* pLsi);
    bool PopTest(pyu::LinearStorageInterface<int>* pLsi);
    bool TopTest(pyu::LinearStorageInterface<int>* pLsi);
    bool ClearTest(pyu::LinearStorageInterface<int>* pLsi);

    static Test_Registrar<StackTests> registrar;
};