#pragma once
#include "memory"

class Data {
public:
    std::shared_ptr<Data> GetNext();
private:
    std::shared_ptr<Data> next_;
};