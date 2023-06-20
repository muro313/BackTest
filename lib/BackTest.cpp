#include "BackTest.h"

BackTest::BackTest(const Model &model, const Exchange &exchange,
                   std::chrono::time_point<std::chrono::system_clock> start,
                   std::chrono::time_point<std::chrono::system_clock> end, std::chrono::system_clock::duration delay,
                   const History &history) :
        model_(std::make_shared<Model>(model)),
        start_(start),
        end_(end),
        delay_(delay),
        history_(std::make_shared<History>(history)) {
}

void BackTest::LoadData() {
    history_->LoadData();
}

void BackTest::Run() {
    in_process_ = true;
    while (in_process_){
        auto data = history_->GetNextData();

        if (!data) {
            Stop();
            break;
        }

        model_->UpDate(data);
        auto orders = model_->GetOrders();

        for (auto& order : orders) {
            order_book_.AddOrd(order);
        }


        auto matchedOrders = order_book_->matchOrders();

        for (auto& matchedOrder : matchedOrders) {
            exchange_->executeOrder(matchedOrder);
        }

        order_book_->updateOrders();
    }
}

double BackTest::CalculatePnl() {
    double pnl = 0.0;
    double position = 0.0;
    double last_price = 0.0;

    for (auto t = start_; t <= end_; t += delay_) {
        auto market_data = exchange_->GetMarketData(t);
        auto decision = model_->MakeSolution(market_data);
        position += decision;

        auto current_price = market_data.GetLastPrice();
        if (last_price != 0.0) {
            pnl += position * (current_price - last_price);
        }
        last_price = current_price;
    }
    return pnl;
}

std::vector<double> BackTest::GetPositionTimeSeries() {
    return std::vector<double>();
}
