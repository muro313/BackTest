#pragma once

#include "memory"
#include "Order.h"
#include <vector>

struct Event {
    Event(const std::shared_ptr<Order<double>> &order, bool is_end_);

    std::shared_ptr<Order<double>> order;
    bool is_end_{};
};

class Data {
public:
    Data() = default;

    void addEvent(const std::shared_ptr<Order<double>> &order, bool is_finish);

    std::vector<std::shared_ptr<Event>> &getEvents();

private:
    std::vector<std::shared_ptr<Event>> events_;
};