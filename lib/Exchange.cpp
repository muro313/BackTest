#include "Exchange.h"

void Exchange::ExecuteOrders(const std::vector<Order<double>> &orders) {
    for(const auto& order: orders){
        ExecuteOrder(order);
    }
}

std::shared_ptr<Data> Exchange::GetMarketData(std::chrono::time_point<std::chrono::system_clock> time) const {
    auto it = std::lower_bound(history_.begin(), history_.end(), time,
                               [](const Data& md, const std::chrono::time_point<std::chrono::system_clock>& t) {
                                   return md.GetTime() < t;
                               });

    if (it == history_.begin()) {
        return *it;
    }
    else if (it == history_.end()) {
        return history_.back();
    }
    else {
        auto it_prev = it - 1;
        auto time_prev = it_prev->GetTime();
        auto time_next = it->GetTime();
        auto weight_next = static_cast<double>((time - time_prev).count()) / (time_next - time_prev).count();
        auto weight_prev = 1.0 - weight_next;
        auto bid_price = it_prev->GetBidPrice() * weight_prev + it->GetBidPrice() * weight_next;
        auto ask_price = it_prev->GetAskPrice() * weight_prev + it->GetAskPrice() * weight_next;
        auto last_price = it_prev->GetLastPrice() * weight_prev + it->GetLastPrice() * weight_next;
        return std::make_shared<Data>(time, bid_price, ask_price, last_price);
    }
}