//#pragma once
//
//#include <chrono>
//#include "Model.h"
//#include "Exchange.h"
//#include "memory"
//#include "History.h"
//
//class BackTest {
//public:
//    BackTest(const Model &model,
//             const Exchange &exchange,
//             std::chrono::time_point<std::chrono::system_clock> start,
//             std::chrono::time_point<std::chrono::system_clock> end,
//             std::chrono::system_clock::duration delay,
//             const History &history);
//
//    void LoadData();
//
//    void Run();
//
//    void Stop();
//
//    void Save();
//
//    double CalculatePnl();
//
//    std::vector<double> GetPositionTimeSeries();
//
//    void SimulateModel();
//private:
//    std::shared_ptr<Model> model_;
//    std::shared_ptr<Exchange> exchange_;
//    std::chrono::time_point<std::chrono::system_clock> start_;
//    std::chrono::time_point<std::chrono::system_clock> end_;
//    std::chrono::system_clock::duration delay_;
//    std::shared_ptr<History> history_;
//    std::shared_ptr<OrderBook<double>> order_book_;
//    bool in_process_;
//};