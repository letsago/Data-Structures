#pragma once

#include <unordered_map>
#include <gtest/gtest.h>

#ifndef MAX_ALLOCATIONS
#define MAX_ALLOCATIONS 25
#endif

#define RED "\033[1;31m"
#define DEFAULT "\033[0m"

class MemoryTracker
{
public:
    void setActive(bool status) { m_active = status; }

    void addAllocation(void* p, size_t size)
    {
        if (!m_active) return;

        if (m_numAllocations == MemoryTracker::s_maxAllocations || !m_state)
        {
            m_state = false;
            return;
        }
        for (uint32_t i = 0; i < MemoryTracker::s_maxAllocations; ++i)
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

        for (uint32_t i = 0; i < MemoryTracker::s_maxAllocations; ++i)
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
        for (uint32_t i = 0; i < MemoryTracker::s_maxAllocations; ++i)
        {
            if (m_data[i] != nullptr) {
                total_bytes += m_size[i];
            }
        }
        return total_bytes;
    }

public:
    static const uint32_t s_invalidState;
    static const uint32_t s_maxAllocations = MAX_ALLOCATIONS;

private:
    void* m_data[MemoryTracker::s_maxAllocations] = { nullptr };
    size_t m_size[MemoryTracker::s_maxAllocations] = {0};
    uint32_t m_numAllocations = 0;
    bool m_active = false;
    bool m_state = true;

};

MemoryTracker& getTracker();

class LeakChecker : public ::testing::EmptyTestEventListener {
  private:
    // Called before a test starts.
    virtual void OnTestStart(const ::testing::TestInfo& test_info) {
        getTracker().setActive(true);
        _starting_leaks = getTracker().NumMemoryLeaks();
    }

    // Called after a test ends.
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        getTracker().setActive(false);
        if (getTracker().NumMemoryLeaks() == MemoryTracker::s_invalidState)
        {
            throw std::range_error(RED  "In sufficent buffer for memory leak validation. Please compile with a larger: MAX_ALLOCATIONS" DEFAULT);
        }
        uint32_t difference = getTracker().NumMemoryLeaks() - _starting_leaks;

        // You can generate a failure in any event handler except
        // OnTestPartResult. Just use an appropriate Google Test assertion to do
        // it.
        ASSERT_EQ(difference, 0) << "Leaked " << difference << " Bytes!";
  }
  uint32_t _starting_leaks;
};
