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
        ADD_TEST(InsertTest);
        ADD_TEST(RemoveTest);
        ADD_TEST(InsertFrontTest);
        ADD_TEST(InsertBackTest);
        ADD_TEST(RemoveFrontTest);
        ADD_TEST(RemoveBackTest);
        ADD_TEST(ClearTest);
        ADD_TEST(AtTest);
        ADD_TEST(ContainsTest);
        ADD_TEST(FindTest);
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
