#pragma once
#include <memory>
#include "History.h"
#include "OrderBook.h"

class Exchange {
public:
    Exchange();
    void ExecuteOrder(const Order<double>& order);
    void ExecuteOrders(const std::vector<Order<double>>& orders);
    std::shared_ptr<Data> GetMarketData(std::chrono::time_point<std::chrono::system_clock> time) const;
//    GetHistory();
private:
    std::shared_ptr<History> history_;
//    std::shared_ptr<OrderBook<double>>
};

