#include <stdexcept>
#include "Portfolio.h"

Portfolio::Portfolio(double dollars, double rubls) :
        balance_dollars_(dollars),
        balance_rubls_(rubls) {
}

void Portfolio::CellRubles(double amount, double price) {
    if (amount > balance_rubls_) {
        throw std::runtime_error("Not enough rubles to cell");
    }
    balance_rubls_ -= amount;
    balance_dollars_ += (amount / price);
}

void Portfolio::BuyRubles(double amount, double price) {
    auto amount_dollars = amount / price;
    if (amount_dollars > balance_dollars_) {
        throw std::runtime_error("Not enough dollars to buy rubles");
    }
    balance_dollars_ -= amount_dollars;
    balance_rubls_ += amount;
}

double Portfolio::BalanceRub() {
    return balance_rubls_;
}

double Portfolio::BalanceDoll() {
    return balance_dollars_;
}
