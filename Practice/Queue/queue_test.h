#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/vector.h>
#include <pyu/linked_list.h>

class QueueTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(QueueTests::PushTest, new pyu::Vector<int>);
        ADD_TEST(QueueTests::PushTest, new pyu::LinkedList<int>);
        ADD_TEST(QueueTests::PopTest, new pyu::Vector<int>);
        ADD_TEST(QueueTests::PopTest, new pyu::LinkedList<int>);
        ADD_TEST(QueueTests::FrontTest, new pyu::Vector<int>);
        ADD_TEST(QueueTests::FrontTest, new pyu::LinkedList<int>);
        ADD_TEST(QueueTests::ClearTest, new pyu::Vector<int>);
        ADD_TEST(QueueTests::ClearTest, new pyu::LinkedList<int>);
    }

private:
    bool PushTest(pyu::LinearStorageInterface<int>* pLsi);
    bool PopTest(pyu::LinearStorageInterface<int>* pLsi);
    bool FrontTest(pyu::LinearStorageInterface<int>* pLsi);
    bool ClearTest(pyu::LinearStorageInterface<int>* pLsi);

    static Test_Registrar<QueueTests> registrar;
};