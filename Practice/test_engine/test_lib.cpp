#include "test_lib.h"

const uint32_t MemoryTracker::s_invalidState = 0xFFFFFFFE;
// const uint32_t MemoryTracker::s_maxAllocations = MAX_ALLOCATIONS;

MemoryTracker& getTracker()
{
    static MemoryTracker s_tracker;
    return s_tracker;
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
