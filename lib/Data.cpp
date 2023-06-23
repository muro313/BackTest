#include "Data.h"

Event::Event(const std::shared_ptr<Order<double>> &order, bool is_end_) : order(order),
                                                                          is_end_(is_end_) {
}

void Data::addEvent(const std::shared_ptr<Order<double>>& order, bool is_finish) {
    events_.push_back(std::make_shared<Event>(order, is_finish));
}

std::vector<std::shared_ptr<Event>> &Data::getEvents() {
    return events_;
}
