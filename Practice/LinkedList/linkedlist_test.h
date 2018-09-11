#pragma once

#include <pyu/test_lib.h>

class LinkedListTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(LinkedListTests::InsertTest);
        ADD_TEST(LinkedListTests::RemoveTest);
        ADD_TEST(LinkedListTests::InsertFrontTest);
        ADD_TEST(LinkedListTests::InsertBackTest);
        ADD_TEST(LinkedListTests::RemoveFrontTest);
        ADD_TEST(LinkedListTests::RemoveBackTest);
        ADD_TEST(LinkedListTests::FindFirstTest);
        ADD_TEST(LinkedListTests::FindManyTest);
        ADD_TEST(LinkedListTests::ClearTest);
        ADD_TEST(LinkedListTests::AssignmentOperatorTest);
        ADD_TEST(LinkedListTests::CopyTest);
        ADD_TEST(LinkedListTests::AtTest);
    }

private:
    static bool InsertTest();
    static bool RemoveTest();
    static bool InsertFrontTest();
    static bool InsertBackTest();
    static bool RemoveFrontTest();
    static bool RemoveBackTest();
    static bool FindFirstTest();
    static bool FindManyTest();
    static bool ClearTest();
    static bool AssignmentOperatorTest();
    static bool CopyTest();
    static bool AtTest();

    static Test_Registrar<LinkedListTests> registrar;
};
