#pragma once

#include <cxxabi.h>
#include <typeindex>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <algorithm>

#ifndef MAX_ALLOCATIONS
#define MAX_ALLOCATIONS 256
#endif

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define DEFAULT "\033[0m"

#define COLOR_LINE(color, statements) (*UnitTests::s_out) << color << statements << DEFAULT << std::endl;
#define PASS_FAIL_LINE(conditional, statements) COLOR_LINE((conditional ? GREEN : RED), (conditional ? "PASSED" : "FAILED") <<"\t" << statements)

#define MEMORY_LEAK(result, starting_leaks, starting_bytes) { \
    bool comp = (getTracker().NumMemoryLeaks() == starting_leaks) & (starting_leaks != MemoryTracker::s_invalidState); \
    PASS_FAIL_LINE(comp, "MEMORY LEAK TEST (bytes: " << getTracker().NumBytesOfError() - starting_bytes << ")" ); \
    result &= comp; \
}

#define __VERIFY(name, comp, valA, valB, print_b) { \
    auto a = valA; \
    auto b = static_cast<std::remove_reference<decltype(valA)>::type>(valB); \
    bool result = (a comp b); \
    (*UnitTests::s_out) \
        << "VERIFY_" << name << "(" \
        << #valA; \
    if(print_b) (*UnitTests::s_out) << ", " << #valB; \
    (*UnitTests::s_out) << ")"; \
    if (!result) { \
        if (print_b) COLOR_LINE(RED, " (" << a << ", " << b << ")") \
        else (*UnitTests::s_out) << std::endl; \
        return false; \
    } \
    (*UnitTests::s_out) << std::endl; \
}

#define VERIFY_EQ(valA, valB) __VERIFY("EQ", ==, valA, valB, true)
#define VERIFY_NOT_EQ(valA, valB) __VERIFY("NOT_EQ", !=, valA, valB, true)
#define VERIFY_TRUE(statement) __VERIFY("TRUE", ==, statement, true, false)
#define VERIFY_FALSE(statement) __VERIFY("FALSE", ==, statement, false, false)
#define DISABLE_TEST(type) UnitTests::setTestStatus(typeid(type), false);
#define ENABLE_TEST(type) UnitTests::setTestStatus(typeid(type), true);
#define SET_OUTPUT(stream) UnitTests::setOutputStream(&stream);

template <typename T> char* get_typename(T& object)
{
    return abi::__cxa_demangle(typeid(object).name(), 0, 0, 0);
}

#define ADD_TEST(test, ...) { \
    std::string test_name(get_typename(*this)); \
    test_name += "::"; \
    test_name += #test; \
    test_name += "("; \
    test_name += #__VA_ARGS__; \
    test_name += ")"; \
    std::string status; \
    bool enabled = UnitTests::s_testMetadata()[typeid(*this)].enabled; \
    if (enabled) \
    { \
        status = "Running"; \
    } \
    else \
    { \
        status = "Skipping"; \
    } \
    COLOR_LINE(YELLOW, status << " test:\t" << test_name) \
    if (enabled) \
    { \
        getTracker().setActive(true); \
        uint32_t _starting_leaks = getTracker().NumMemoryLeaks(); \
        uint32_t _starting_bytes = getTracker().NumBytesOfError(); \
        auto start_time = std::chrono::high_resolution_clock::now(); \
        bool result = test(__VA_ARGS__); \
        auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time; \
        getTracker().setActive(false); \
        MEMORY_LEAK(result, _starting_leaks, _starting_bytes); \
        uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count(); \
        UnitTests::s_summary.push_back({test_name, result ? UnitTests::TestResult::PASSED : UnitTests::TestResult::FAILED, us}); \
        PASS_FAIL_LINE(result, test_name); \
        COLOR_LINE(BLUE, "Time taken: " << us << " us" << std::endl ); \
    } \
    else \
    { \
        UnitTests::s_summary.push_back({test_name, UnitTests::TestResult::SKIPPED, 0}); \
    }  \
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
            std::cerr << RED << "TOO MANY ALLOCATIONS. PLEASE INCREASE SIZE." << DEFAULT << std::endl;
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

    uint32_t NumBytesOfError()
    {
        uint32_t total_bytes = 0;
        for (uint32_t i = 0; i < MAX_ALLOCATIONS; ++i)
        {
            if (m_data[i] != nullptr) {
                total_bytes += m_size[i];
            }
        }
        return total_bytes;
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
struct TestMetadata
{
    bool enabled = true;
};
typedef std::unordered_map<std::type_index, UnitTests*(*)()> typemap;
typedef std::unordered_map<std::type_index, TestMetadata> infomap;

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

    static void setTestStatus(std::type_index t, bool status) {
        s_testMetadata()[t].enabled = status;
    }

    static void setOutputStream(std::ostream* stream) {
        UnitTests::s_out = stream;
    }

private:
    static typemap & s_registry();
    void Run()
    {
        (*UnitTests::s_out) << "---------------------------------------------" << std::endl;
        (*UnitTests::s_out) << "-----------       UnitTests      ------------" << std::endl;
        (*UnitTests::s_out) << "---------------------------------------------" << std::endl;

        RunTests();
    }

    static void Summary()
    {
        (*UnitTests::s_out) << "---------------------------------------------" << std::endl;
        (*UnitTests::s_out) << "-----------        Summary       ------------" << std::endl;
        (*UnitTests::s_out) << "---------------------------------------------" << std::endl;

        std::sort (s_summary.begin(), s_summary.end(), [](const UnitTests::TestStats& a, const UnitTests::TestStats& b) {
            if (a.result != b.result)
            {
                return static_cast<int>(a.result) > static_cast<int>(b.result);
            }

            if (a.duration != b.duration)
            {
                return a.duration > b.duration;
            }

            return a.name < b.name;
        });

        int passed = 0;
        int total = 0;
        int skipped = 0;
        (*UnitTests::s_out) << BLUE << "Time Taken\t" << GREEN << "Status\tTest Name" << DEFAULT << std::endl;
        for (auto& it : s_summary)
        {
            (*UnitTests::s_out) << BLUE << std::setfill(' ') << std::setw(10) << it.duration << "\t" << DEFAULT;
            if (it.result == TestResult::SKIPPED)
            {
                COLOR_LINE(YELLOW, "SKIPPED\t" << it.name);
                skipped += 1;
            }
            else
            {
                PASS_FAIL_LINE(static_cast<int>(it.result), it.name)
                passed += static_cast<int>(it.result);
            }
            total += 1;
        }
        if (skipped) (*UnitTests::s_out) << "Test skipped:\t" << skipped  << " / " << total << std::endl;
        (*UnitTests::s_out) << "Test passed:\t" << passed  << " / " << total << std::endl;
    }

protected:
    enum class TestResult : int
    {
        FAILED = 0,
        PASSED,
        SKIPPED
    };

    struct TestStats
    {
        std::string name;
        TestResult result;
        uint64_t duration;
    };

    UnitTests() = default;
    virtual ~UnitTests() = default;
    virtual void RunTests() = 0;
    static uint32_t s_refCounters;
    static std::vector<TestStats> s_summary;
    static infomap & s_testMetadata();
    static std::ostream* s_out;
    static std::string s_summaryFile;

    template<typename U> friend class Test_Registrar;
};

template <typename T>
class Test_Registrar
{
public:
    Test_Registrar() {
        UnitTests::s_registry()[typeid(T)] = &Test_Registrar::createInstance;
        UnitTests::s_testMetadata()[typeid(T)] = TestMetadata();
    }
private:
    static UnitTests* createInstance() { return new T; }
};
