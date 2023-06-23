#include "BackTest.h"

#include <utility>
#include <iomanip>


BackTest::BackTest(std::shared_ptr<History> history, std::shared_ptr<Model> model,
                   std::chrono::time_point<std::chrono::system_clock> start,
                   std::chrono::time_point<std::chrono::system_clock> end,
                   std::chrono::system_clock::duration delay,
                   const std::string &file_name) :
        history_(std::move(history)), model_(std::move(model)),
        start_(start),
        end_(end),
        delay_(delay), os_(std::ofstream(file_name)) {
    for (auto data = history_->begin(); data != history_->end(); ++data) {
        if (data->first >= start_) {//time
            now_ = data;
            break;
        }
        for (const auto &event: data->second.getEvents()) {
            if (event->is_end_) {
                model_->RemoveOrder(event->order);
                continue;
            }
            model_->AddOrder(event->order);
        }
    }
}

void BackTest::LoadData() {
    history_->LoadData();
}

void BackTest::Run() {
    in_process_ = true;
    while (in_process_) {
        if (now_ == history_->end()) {
            Stop();
            return;
        }
        if (now_->first > end_) {
            Stop();
            return;
        }
        auto buy_price = model_->GetMinBuyPrice();
        auto sell_price = model_->GetMaxSellPrice();
        for (auto &event: now_->second.getEvents()) {
            if (event->is_end_) {
                model_->RemoveOrder(event->order);
                continue;
            }
            model_->AddOrder(event->order);
        }
        auto decision = model_->MakeDecision(sell_price, buy_price);
        decision->time = now_->first;
        decisions_.push_back(decision);
    }
}

void BackTest::Stop() {
    in_process_ = false;
}


void BackTest::SimulateModel() {
    double pnl_roubles = 0;
    double pnl_dollars = 0;
    const int width = 20;
    PrintNewline(width * 4 + 3);
    PrintWord("Date", width);
    PrintWord("Type", width);
    PrintWord("Exchange ratio", width);
    PrintWord("Change in dollars", width);
    PrintWord("Change in roubles", width);
    PrintNewline(width * 4 + 3);
    for (const auto &decision: decisions_) {
        auto changes_in_dollars = decision->amount / decision->price;
        auto changes_in_rubles = decision->amount;
        PrintDate(decision->time, width);
        if (decision->buy) {
            PrintWord("Change dollars to rubles", width);
            changes_in_dollars *= -1;
        } else {
            PrintWord("Change rubles to dollars", width);
            changes_in_rubles *= -1;
        }
        PrintNum(decision->price, width);
        PrintNum(changes_in_dollars, width);
        PrintNum(changes_in_rubles, width);
        pnl_dollars += changes_in_dollars;
        pnl_roubles += changes_in_rubles;
        os_ << '\n';
    }
    PrintNewline(width * 4 + 3);
    PrintWord("Profit(Loss) in dollars:", width);
    PrintWord("Profit(Loss) in rubles:", width);
    os_ << '\n';
    PrintNum(pnl_dollars, width);
    PrintNum(pnl_roubles, width);
}

void BackTest::PrintNewline(int width) {
    os_.width(width);
    os_.fill('-');
    os_ << '\n';
}

void BackTest::PrintNum(double num, int width) {
    os_.width(width);
    os_ << num;
    os_ << '|';
}

void BackTest::PrintWord(const std::string &word, int width) {
    os_.width(width);
    os_ << word;
    os_ << '|';
}

void BackTest::PrintDate(const std::chrono::system_clock::time_point &time, int width) {
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::localtime(&tt);
    std::ostringstream ss;

    ss << std::setfill('0') << std::setw(2) << tm.tm_hour << ":"
       << std::setfill('0') << std::setw(2) << tm.tm_min << ":"
       << std::setfill('0') << std::setw(2) << tm.tm_sec << " "
       << std::setfill('0') << std::setw(2) << tm.tm_mday << "."
       << std::setfill('0') << std::setw(2) << tm.tm_mon + 1 << "."
       << tm.tm_year + 1900;

    std::string output = ss.str();

    PrintWord(output, width);
}

