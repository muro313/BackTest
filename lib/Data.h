#pragma once

#include "memory"
#include "Order.h"
#include <vector>

class Data {
public:
    Data() = default;

    void addOrder(const Order<double> &order, bool is_finish);

    std::shared_ptr<Order<double>> getOrder(size_t order);

    bool isFinish(size_t order);

private:
    size_t orders_amount_ = 0;
    std::vector<std::shared_ptr<Order<double>>> orders_;
    std::vector<bool> is_finish_;
};