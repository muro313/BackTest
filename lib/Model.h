#pragma once

#include "Portfolio.h"
#include "History.h"
#include "Order.h"
#include "Robot.h"
#include <vector>
#include <memory>


class Model {
public:
    Model();
private:
    std::shared_ptr<Portfolio> portfolio_;
    std::shared_ptr<History> history_;
    std::shared_ptr<Robot> robot_;
};
