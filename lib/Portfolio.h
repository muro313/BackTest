#pragma once

class Portfolio {
public:
    Portfolio() = default;

    Portfolio(double dollars,
              double rubls);

    void CellRubles(double amount, double price);

    void BuyRubles(double amount, double price);

    double BalanceRub();

    double BalanceDoll();

private:
    double balance_rubls_;
    double balance_dollars_;
};

