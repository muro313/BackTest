#include <gtest/gtest.h>
#include "OrderBook.h"

TEST(OrderBookTest, Empty) {
    OrderBook<int> order_book;
    EXPECT_EQ(order_book.BidAmount(), 0);
    EXPECT_EQ(order_book.AskAmount(), 0);
    EXPECT_ANY_THROW(order_book.GetMinBid());
    EXPECT_ANY_THROW(order_book.GetMaxAsk());
}

TEST(OrderBookTest, Instructor) {
    std::vector<Order<size_t>> orders;
    const size_t ask_begin = 0;
    const size_t ask_end = 100;
    const size_t bid_begin = 200;
    const size_t bid_end = 300;
    for (size_t i = ask_begin; i <= ask_end; ++i) {
        orders.emplace_back(i, i, true);
    }
    for (size_t i = bid_begin; i <= bid_end; ++i) {
        orders.emplace_back(i, i, false);
    }
    OrderBook<size_t> order_book(orders);
    EXPECT_EQ(order_book.GetMaxAsk(), ask_end);
    EXPECT_EQ(order_book.GetMinBid(), bid_begin);
    EXPECT_EQ(order_book.BidAskSpread(), bid_begin - ask_end);
}


TEST(OrderBookTest, Adders) {
    OrderBook<size_t> order_book;
    size_t order_price = 100;
    size_t order_volume = 24;
    Order order(order_price, order_volume, false);
    order_book.AddOrd(order);
    EXPECT_EQ(order_book.GetVolume(order_price), order_volume);

    order_book.AddOrd(order);
    EXPECT_EQ(order_book.GetVolume(order_price), order_volume * 2);
    EXPECT_ANY_THROW(order_book.RemoveOrder(Order(order_price, order_volume*100)));

    order.IncreaseVolume(order_volume);
    order_book.RemoveOrder(order);
    EXPECT_EQ(order_book.GetVolume(order_price), 0);
}