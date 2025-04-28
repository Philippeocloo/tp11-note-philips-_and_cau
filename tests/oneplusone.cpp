#include <main.h>
#include <gtest/gtest.h>

TEST(TestTestSuite, OnePlusOneEqualsTwo) {
    ASSERT_EQ(oneplusone(), 2);
}