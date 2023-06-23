#include <gtest/gtest.h>
#include "Portfolio.h"

TEST(PortfolioTest, Empty) {
    Portfolio portfolio{};
    EXPECT_DOUBLE_EQ(portfolio.BalanceDoll(), 0.0);
    EXPECT_DOUBLE_EQ(portfolio.BalanceRub(), 0.0);
    EXPECT_ANY_THROW(portfolio.BuyRubles(10000, 92.3));
    EXPECT_ANY_THROW(portfolio.BuyRubles(10000, 85.2));
}

TEST(PortfolioTest, Buy) {
    double dollars = 1000;
    double rubles = 10000;
    Portfolio portfolio(dollars, rubles);
    portfolio.BuyRubles(1000, 100);
    rubles = 11000;
    dollars = 990;
    EXPECT_DOUBLE_EQ(portfolio.BalanceRub(), rubles);
    EXPECT_DOUBLE_EQ(portfolio.BalanceDoll(), dollars);
    portfolio.CellRubles(11000, 100);
    EXPECT_ANY_THROW(portfolio.CellRubles(1, 2));
}