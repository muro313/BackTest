#pragma once

#include <cstddef>
#include <chrono>

class Time {
    Time(int hours,
         int mins,
         int secs,
         int days = 0,
         int months = 0,
         int years = 0);
    void RUN();

    void Stop();

private:
    int second_;
    int minute_;
    int hour_;
    int day_;
    int month_;
    int year_;
    bool is_running_ = false;
    std::chrono::system_clock::time_point last_stop_;
};
