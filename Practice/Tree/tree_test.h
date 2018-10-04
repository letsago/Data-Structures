#pragma once

#include <gtest/gtest.h>
#include <pyu/tree.h>

class SortedTreeTests : public ::testing::Test
{
protected:
    // Functions used in the test
    void validateSorted(const pyu::Tree<int>& other, const pyu::Vector<int>& sorted)
    {
        ASSERT_EQ(other.size(), sorted.length());

        ASSERT_TRUE(other.contains(sorted.at(0)));
        for (uint32_t i = 1; i < sorted.length(); ++i)
        {
            ASSERT_TRUE(other.contains(sorted.at(i)));
            ASSERT_LE(sorted.at(i - 1), sorted.at(i));
        }
    }
};
