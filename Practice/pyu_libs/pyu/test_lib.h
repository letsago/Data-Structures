#pragma once

#include <typeindex>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

#ifndef MAX_ALLOCATIONS
#define MAX_ALLOCATIONS 256
#endif

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define DEFAULT "\033[0m"

#define COLOR_LINE(color, statements) std::cout << color << statements << DEFAULT << std::endl;
#define PASS_FAIL_LINE(conditional, statements) COLOR_LINE((conditional ? GREEN : RED), (conditional ? "PASSED" : "FAILED") <<"\t" << statements)

#define MEMORY_LEAK(result, starting_leaks) { \
    bool comp = (getTracker().NumMemoryLeaks() == starting_leaks) & (starting_leaks != MemoryTracker::s_invalidState); \
    PASS_FAIL_LINE(comp, "MEMORY LEAK TEST"); \
    result &= comp; \
}

#define __VERIFY(name, comp, valA, valB, print_b) { \
    auto a = valA; \
    auto b = static_cast<std::remove_reference<decltype(valA)>::type>(valB); \
    bool result = (a comp b); \
    std::cout \
        << "VERIFY_" << name << "(" \
        << #valA; \
    if(print_b) std::cout << ", " << #valB; \
    std::cout << ")"; \
    if (!result) { \
        if (print_b) COLOR_LINE(RED, " (" << a << ", " << b << ")") \
        else std::cout << std::endl; \
        return false; \
    } \
    std::cout << std::endl; \
}

#define VERIFY_EQ(valA, valB) __VERIFY("EQ", ==, valA, valB, true)
#define VERIFY_NOT_EQ(valA, valB) __VERIFY("NOT_EQ", !=, valA, valB, true)
#define VERIFY_TRUE(statement) __VERIFY("TRUE", ==, statement, true, false)
#define VERIFY_FALSE(statement) __VERIFY("FALSE", ==, statement, false, false)

#define ADD_TEST(test, ...) { \
    COLOR_LINE(YELLOW, "Running test:\t" << #test) \
    getTracker().setActive(true); \
    uint32_t _staring_leaks = getTracker().NumMemoryLeaks(); \
    bool result = test(__VA_ARGS__); \
    getTracker().setActive(false); \
    MEMORY_LEAK(result, _staring_leaks); \
    UnitTests::s_summary.push_back(std::make_pair(#test, result)); \
    PASS_FAIL_LINE(result, #test << std::endl ) \
}

class MemoryTracker
{
public:
    void setActive(bool status) { m_active = status; }

    void addAllocation(void* p, size_t size) 
    {
        if (!m_active) return;
        
        if (m_numAllocations == MAX_ALLOCATIONS || !m_state)
        {
            std::cout << RED << "TOO MANY ALLOCATIONS. PLEASE INCREASE SIZE." << DEFAULT << std::endl;
            m_state = false;
            return;
        }
        for (uint32_t i = 0; i < MAX_ALLOCATIONS; ++i)
        {
            if (m_data[i] == nullptr)
            {
                m_data[i] = p;
                m_size[i] = size;
                m_numAllocations++;
                break;
            }
        }
    }

    void freeAllocations(void* p)
    {
        if (!m_active) return;

        for (uint32_t i = 0; i < MAX_ALLOCATIONS; ++i)
        {
            if (m_data[i] == p) {
                m_data[i] = nullptr;
                m_size[i] = 0;
                --m_numAllocations;
                return;
            }
        }
    }

    uint32_t NumMemoryLeaks() 
    {
        return m_state ? m_numAllocations : s_invalidState;
    }

private:
    void* m_data[MAX_ALLOCATIONS] = { nullptr };
    size_t m_size[MAX_ALLOCATIONS] = {0};
    uint32_t m_numAllocations = 0;
    bool m_active = false;
    bool m_state = true;

public:
    static const uint32_t s_invalidState = 0xFFFFFFFF;
};

MemoryTracker& getTracker();

class UnitTests;
typedef std::map<std::type_index, UnitTests*(*)()> typemap;

class UnitTests
{
public:
    static void Run_All() {
        auto data = UnitTests::s_registry();
        for (auto& it : data)
        {
            auto test = it.second();
            test->Run();
            delete test;
        }
        UnitTests::Summary();
    }

private:
    static typemap & s_registry();
    void Run()
    {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "-----------       UnitTests      ------------" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;

        RunTests();
    }
    
    static void Summary()
    {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "-----------        Summary       ------------" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        
        int passed = 0;
        int total = 0;
        for (auto& it : s_summary)
        {
            PASS_FAIL_LINE(it.second, it.first)
            passed += it.second;
            total += 1;
        }
        std::cout << "Test passed:\t" << passed  << " / " << total << std::endl;
    }

protected:
    UnitTests() = default;
    virtual ~UnitTests() = default;
    virtual void RunTests() = 0;   
    static uint32_t s_refCounters;    
    static std::vector<std::pair<std::string, bool>> s_summary;
    
    template<typename U> friend class Test_Registrar;
};

template <typename T>
class Test_Registrar
{
public:
    Test_Registrar() { UnitTests::s_registry()[typeid(T)] = &Test_Registrar::createInstance; }
private:
    static UnitTests* createInstance() { return new T; }
};
