#include <gtest/gtest.h>
#include "Order.h"

TEST(OrderTest, Empty) {
    Order order(0);
    EXPECT_EQ(order.GetPrice(), 0);
    EXPECT_EQ(order.GetVolume(), 0);
    EXPECT_TRUE(order.IsAsk());
    EXPECT_FALSE(order.IsBid());
}

TEST(OrderTest, Setters) {
    size_t price = 1200;
    size_t volume = 2000;
    Order order(price, volume);
    EXPECT_EQ(order.GetPrice(), price);
    EXPECT_EQ(order.GetVolume(), volume);
    volume += 1000;
    order.IncreaseVolume(1000);
    EXPECT_EQ(order.GetVolume(), volume);
    EXPECT_ANY_THROW(order.DecreaseVolume(40000));
}

TEST(OrderTest, TypeChange){
    Order bid(0, 0, false);
    EXPECT_FALSE(bid.IsAsk());
    EXPECT_TRUE(bid.IsBid());
    bid.ChangeType();
    EXPECT_TRUE(bid.IsAsk());
    EXPECT_FALSE(bid.IsBid());
}
