#pragma once

#include "OrderBook.h"

#include "Portfolio.h"
#include <memory>

struct Decision {
    double amount{};
    double price{};
    bool buy{};
    std::chrono::system_clock::time_point time;
};

class Robot {
public:
    Robot(const Portfolio &profilo,
          const OrderBook<double> &order_book,
          double prev_cell_price = 0,
          double prev_buy_price = 0);

    Decision MakeDesicion(std::chrono::system_clock::time_point &time_point);

private:
    std::shared_ptr<Portfolio> portfolio_;
    std::shared_ptr<OrderBook<double>> order_book_;
};