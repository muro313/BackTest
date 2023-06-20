#pragma once

#include "Portfolio.h"
#include "History.h"
#include "Order.h"
#include <vector>
#include <memory>


class Model {
public:
    Model();

    void UpDate(std::shared_ptr<Data> new_data);

    void MakeSolution();

    std::vector<Order<double>> &GetOrders() {
        return orders_;
    }

private:
    std::shared_ptr<Portfolio> portfolio_;
    std::shared_ptr<History> history_;
    std::vector<Order<double>> orders_;
};
