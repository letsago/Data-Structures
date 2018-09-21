#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>
#include <pyu/tree.h>

class TreeTests : public UnitTests
{
protected:

    void RunTests() final
    {
        ADD_TEST(InsertTest);
        ADD_TEST(RemoveRootTest);
        ADD_TEST(RemoveLeafTest);
        ADD_TEST(ClearTest);
        ADD_TEST(ContainsTest);
    }

private:
    bool InsertTest();
    bool RemoveRootTest();
    bool RemoveLeafTest();
    bool ClearTest();
    bool ContainsTest();

    static Test_Registrar<TreeTests> registrar;
};
