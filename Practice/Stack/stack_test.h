#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/vector.h>
#include <pyu/linked_list.h>

class StackTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(StackTests::PushTest, new pyu::Vector<int>);
        ADD_TEST(StackTests::PushTest, new pyu::LinkedList<int>);
        ADD_TEST(StackTests::PopTest, new pyu::Vector<int>);
        ADD_TEST(StackTests::PopTest, new pyu::LinkedList<int>);
        ADD_TEST(StackTests::TopTest, new pyu::Vector<int>);
        ADD_TEST(StackTests::TopTest, new pyu::LinkedList<int>);
        ADD_TEST(StackTests::ClearTest, new pyu::Vector<int>);
        ADD_TEST(StackTests::ClearTest, new pyu::LinkedList<int>);
    }

private:
    bool PushTest(pyu::LinearStorageInterface<int>* pLsi);
    bool PopTest(pyu::LinearStorageInterface<int>* pLsi);
    bool TopTest(pyu::LinearStorageInterface<int>* pLsi);
    bool ClearTest(pyu::LinearStorageInterface<int>* pLsi);

    static Test_Registrar<StackTests> registrar;
};