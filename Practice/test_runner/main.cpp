#include <gtest/gtest.h>
#include "../test_engine/test_lib.h"
#include <iostream>
#include <string>

typedef void (*ForParameter)(void);
static std::unordered_map<std::string, ForParameter> kArgMap;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    kArgMap.emplace(std::string("--check_for_leaks"), []() {
        testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
        listeners.Append(new LeakChecker);
    });

    std::string paramList = "Parameter List:\n";
    for (auto it : kArgMap)
    {
        paramList += "\t" + it.first + "\n";
    }
    
    for (int i = 1; i < argc; ++i)
    {
        auto it = kArgMap.find(argv[i]);
        if (it == kArgMap.end())
        {
            std::cout << std::endl << RED << "Arguement not understood: " << argv[i] << DEFAULT << std::endl << std::endl;

            std::cout << "Usage is: " << argv[0] << " [optional parameters]" << std::endl << std::endl;
            std::cout << paramList << std::endl;
            
            exit(-1);
        }

        (*it->second)();
    }

    return RUN_ALL_TESTS();
}
