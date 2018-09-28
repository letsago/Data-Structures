#pragma once

#include <pyu/test_lib.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/shared_ptr.h>

class LinearStorageInterfaceTests : public UnitTests
{
protected:
    virtual pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI() = 0;
    virtual pyu::shared_ptr<pyu::LinearStorageInterface<int>> createTestLSI(pyu::shared_ptr<pyu::LinearStorageInterface<int>>& other) = 0;

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
        ADD_TEST(EqualityTest);
        ADD_TEST(AssignmentTest);
        ADD_TEST(CopyTest);
        ADD_TEST(IteratorUseTest);
        ADD_TEST(IteratorBoundsTest);
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
    bool EqualityTest();
    bool AssignmentTest();
    bool CopyTest();
    bool IteratorUseTest();
    bool IteratorBoundsTest();
};
