#pragma once

#include <chrono>
#include <fstream>
#include "Model.h"
#include "memory"
#include "History.h"

class BackTest {
public:
    BackTest(std::shared_ptr<History> history,
             std::shared_ptr<Model> model,
             std::chrono::time_point<std::chrono::system_clock> start,
             std::chrono::time_point<std::chrono::system_clock> end,
             std::chrono::system_clock::duration delay,
             const std::string& file_name
    );

    void LoadData();

    void Run();

    void Stop();

    double CalculatePnl();

    std::vector<double> GetPositionTimeSeries();

    void SimulateModel();

private:

    void PrintNewline(int width);

    void PrintNum(double num, int width);

    void PrintWord(const std::string &word, int width);

    void PrintDate(const std::chrono::system_clock::time_point &time, int width);

    std::shared_ptr<Model> model_;
    std::shared_ptr<History> history_;
    std::chrono::time_point<std::chrono::system_clock> start_;
    std::chrono::time_point<std::chrono::system_clock> end_;
    std::chrono::system_clock::duration delay_;
    std::shared_ptr<OrderBook<double>> order_book_;
    bool in_process_ = false;
    decltype(history_->begin()) now_;
    std::vector<std::shared_ptr<Decision>> decisions_;
    std::ofstream os_;
};