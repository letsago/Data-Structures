#pragma once

#include <pyu/test_lib.h>

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
        ADD_TEST(DepthTest);
        ADD_TEST(PrintBalancedTreeTest);
        ADD_TEST(PrintNonBalancedTreeTest);
        ADD_TEST(PrintBigBalancedTreeTest);
        ADD_TEST(PrintBigNonBalancedTreeTest);
        ADD_TEST(PrintRightSkewedTreeTest);
        ADD_TEST(PrintLeftSkewedTreeTest);
        ADD_TEST(PrintNullTreeTest);

    }

private:
    bool InsertTest();
    bool RemoveRootTest();
    bool RemoveLeafTest();
    bool ClearTest();
    bool ContainsTest();
    bool DepthTest();
    bool PrintBalancedTreeTest();
    bool PrintNonBalancedTreeTest();
    bool PrintBigBalancedTreeTest();
    bool PrintBigNonBalancedTreeTest();
    bool PrintRightSkewedTreeTest();
    bool PrintLeftSkewedTreeTest();
    bool PrintNullTreeTest();

    static Test_Registrar<TreeTests> registrar;
};
