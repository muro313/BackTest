//
//#include <stdexcept>
//#include "Time.h"
//
//Time::Time(int hours, int mins, int secs, int days, int months, int years)
//        :
//        hour_(hours),
//        minute_(mins),
//        second_(secs),
//        month_(months),
//        year_(years) {
//}
//
//void Time::RUN() {
//    if (is_running_) {
//        throw std::runtime_error("Already running");
//    }
//    is_running_ = true;
//    last_stop_ = std::chrono::system_clock::now();
//}
//
//void Time::Stop() {
//    if(!is_running_){
//        throw std::runtime_error("Already stopped");
//    }
//    is_running_ = false;
//    auto change =
//}
