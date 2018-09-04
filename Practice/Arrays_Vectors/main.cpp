#include <iostream>
#include "headers/sample_test.h"

// To compile:
// g++ main.cpp sample_test.cpp test_helpers.cpp -std=c++14 -o a.out

int main()
{
    UnitTests::Run_All();
    
    return 0;
}