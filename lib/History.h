#pragma once

#include <memory>
#include "Data.h"

class History {
public:
    History() = default;

    History(std::string file_name);

    void LoadData();

    std::shared_ptr<Data> GetNextData();


private:
    std::string file_name_;
    std::shared_ptr<Data> current_data_;
};

