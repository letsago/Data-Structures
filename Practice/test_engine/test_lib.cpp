#include "test_lib.h"

#ifndef MAX_ALLOCATIONS
#define MAX_ALLOCATIONS 25
#endif

class MemoryTracker
{
public:
    void setActive(bool status) { 
        m_active = status; 
        std::cout << "Status: " << status << std::endl;
    }

    void addAllocation(void* p, size_t size)
    {
        if (!m_active) return;
        std::cout << "Allocing.. " << p << " " << size << std::endl;

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
        std::cout << "Deleting.. " << p << std::endl;

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
    static const uint32_t s_invalidState = 0xFFFFFFFF;
    static const uint32_t s_maxAllocations = MAX_ALLOCATIONS;

private:
    void* m_data[MemoryTracker::s_maxAllocations] = { nullptr };
    size_t m_size[MemoryTracker::s_maxAllocations] = {0};
    uint32_t m_numAllocations = 0;
    bool m_active = false;
    bool m_state = true;
};

MemoryTracker& getTracker()
{
    static MemoryTracker s_tracker;
    return s_tracker;
}

void LeakChecker::OnTestStart(const ::testing::TestInfo& test_info) {
    getTracker().setActive(true);
    _starting_leaks = getTracker().NumBytesOfError();
}

void LeakChecker::OnTestEnd(const ::testing::TestInfo& test_info) {
    getTracker().setActive(false);
    if (getTracker().NumMemoryLeaks() == MemoryTracker::s_invalidState)
    {
        throw std::range_error(RED  "In sufficent buffer for memory leak validation. Please compile with a larger: MAX_ALLOCATIONS" DEFAULT);
    }
    uint32_t difference = getTracker().NumBytesOfError() - _starting_leaks;
    
    if (difference > 0)
    {
        FAIL() << RED << "MEMORY LEAK (bytes: " << difference << ")" << DEFAULT;
    }
}

void* operator new(size_t size)
{
    void* p = malloc(size);
    getTracker().addAllocation(p, size);
    return p;
}

void operator delete(void* p) noexcept
{
    getTracker().freeAllocations(p);
    free(p);
}
