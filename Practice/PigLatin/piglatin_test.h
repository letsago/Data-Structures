#pragma once

#include "piglatin.h"
#include <gtest/gtest.h>
#include <pyu/vector.h>

class PigLatinTests : public ::testing::Test
{
  protected:
    // Functions used in the test
    void pigLatinTester(const char input[], const int input_size, const char* output)
    {
        pyu::Vector<char> A(input, input_size);
        pyu::Vector<char> B;
        ASSERT_TRUE(pigLatinTranslate(A, B));
        ASSERT_STREQ(B.data(), output);
    }
};
