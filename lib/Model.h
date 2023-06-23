#pragma once

#include "Portfolio.h"
#include "History.h"
#include "Order.h"
#include "OrderBook.h"
#include <vector>
#include <memory>

struct Decision {
    double amount{};
    double price{};
    bool buy{};
    std::chrono::system_clock::time_point time;
};

class Model {
public:
    explicit Model(const Portfolio &portfolio);

    std::shared_ptr<Decision>
    MakeDecision(const double prev_sell,
                 const double prev_buy);

    void AddOrder(const std::shared_ptr<Order<double>> &order);

    void RemoveOrder(const std::shared_ptr<Order<double>> &order);


    double GetMinBuyPrice();

    double GetMaxSellPrice();

private:
    std::shared_ptr<Portfolio> portfolio_;
    std::shared_ptr<OrderBook<double>> order_book_;
};
