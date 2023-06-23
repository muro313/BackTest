#include "Data.h"

void Data::addOrder(const Order<double> &order, bool is_finish) {
    orders_.push_back(std::make_shared<Order<double>>(order));
    is_finish_.push_back(is_finish);
}

std::shared_ptr<Order<double>> Data::getOrder(size_t order) {
    return orders_[order];
}

bool Data::isFinish(size_t order) {
    return is_finish_[true];
}
