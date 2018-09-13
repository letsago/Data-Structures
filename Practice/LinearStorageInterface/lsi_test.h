#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>

class LinearStorageInterfaceTests : public UnitTests
{
protected:
    virtual pyu::LinearStorageInterface<int>* createTestLSI() = 0;
    virtual bool CopyTest() = 0;
    virtual bool AssignmentTest() = 0;

    void RunTests()
    {
        ADD_TEST(LinearStorageInterfaceTests::InsertTest);
        ADD_TEST(LinearStorageInterfaceTests::RemoveTest);
        ADD_TEST(LinearStorageInterfaceTests::InsertFrontTest);
        ADD_TEST(LinearStorageInterfaceTests::InsertBackTest);
        ADD_TEST(LinearStorageInterfaceTests::RemoveFrontTest);
        ADD_TEST(LinearStorageInterfaceTests::RemoveBackTest);
        ADD_TEST(LinearStorageInterfaceTests::ClearTest);
        ADD_TEST(LinearStorageInterfaceTests::AtTest);
        ADD_TEST(LinearStorageInterfaceTests::ContainsTest);
        ADD_TEST(LinearStorageInterfaceTests::FindTest);
    }

private:
    bool InsertTest();
    bool RemoveTest();
    bool InsertFrontTest();
    bool InsertBackTest();
    bool RemoveFrontTest();
    bool RemoveBackTest();
    bool ClearTest();
    bool AtTest();
    bool ContainsTest();
    bool FindTest();
};
