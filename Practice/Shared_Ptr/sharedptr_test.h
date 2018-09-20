#pragma once

#include <pyu/test_lib.h>
#include <lsi_test.h>

class SharedPtrTests : public UnitTests
{
protected:

    void RunTests() final
    {     
        ADD_TEST(FundamentalTypeTest);
        ADD_TEST(ClassTypeTest);
        ADD_TEST(ScopeTest);
        ADD_TEST(MemoryTest);
    }

private:
    bool FundamentalTypeTest();
    bool ClassTypeTest();
    bool ScopeTest();
    bool MemoryTest();

    static Test_Registrar<SharedPtrTests> registrar;
}; 
