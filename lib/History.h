#pragma once

#include <memory>
#include <map>
#include "Data.h"

class History {
public:
    using Iterator = decltype(std::map<std::chrono::system_clock::time_point, Data>())::iterator;

    explicit History(std::string file_name);

    void LoadData();

    Iterator begin();

    Iterator end();


private:
    std::string file_name_;
    std::map<std::chrono::system_clock::time_point, Data> data_;
};

