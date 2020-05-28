#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

/* using namespace testing; */
extern "C" {
#include "sqr_eq.h"
}

TEST(sqr_eq_sol, no_sol) {
    solution res = solve_eq(2, 2, 1);
    EXPECT_EQ(NO_SOL, res.sol_count);
}

TEST(sqr_eq_sol, one_sol) {
    solution res = solve_eq(4, 4, 1);
    EXPECT_EQ(ONE_SOL, res.sol_count);
    EXPECT_DOUBLE_EQ(-0.5, res.x1);
}

TEST(sqr_eq_sol, two_sols_1) {
    solution res = solve_eq(1, 4, 0);
    EXPECT_EQ(TWO_SOL, res.sol_count);
    EXPECT_DOUBLE_EQ(-4.0, res.x1);
    EXPECT_DOUBLE_EQ(0.0, res.x2);
}

TEST(sqr_eq_sol, two_sols_2) {
    solution res = solve_eq(2, -5, 2);
    EXPECT_EQ(TWO_SOL, res.sol_count);
    EXPECT_DOUBLE_EQ(0.5, res.x1);
    EXPECT_DOUBLE_EQ(2.0, res.x2);
}

TEST(sqrt_eq_sol, stranger_things_1) {
    solution res = solve_eq(1, 0, 0);
    EXPECT_EQ(ONE_SOL, res.sol_count);
    EXPECT_DOUBLE_EQ(0.0, res.x1);
}

TEST(sqrt_eq_sol, stranger_things_2) {
    solution res = solve_eq(0, 1, 0);
    EXPECT_EQ(ONE_SOL, res.sol_count);
    EXPECT_DOUBLE_EQ(0.0, res.x1);
}

TEST(sqrt_eq_sol, stranger_things_3) {
    solution res = solve_eq(0, 0, 1);
    EXPECT_EQ(NO_SOL, res.sol_count);
}

TEST(sqrt_eq_sol, stranger_things_4) {
    solution res = solve_eq(0, 0, 0);
    EXPECT_EQ(NO_SOL, res.sol_count);
}
