#pragma once

#include <gtest/gtest.h>

#define RED "\033[1;31m"
#define DEFAULT "\033[0m"

class LeakChecker : public ::testing::EmptyTestEventListener {
  private:
    virtual void OnTestStart(const ::testing::TestInfo& test_info);
    virtual void OnTestEnd(const ::testing::TestInfo& test_info);

  private:
    uint32_t _starting_leaks;
};
