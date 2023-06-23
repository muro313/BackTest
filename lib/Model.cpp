#include "Model.h"


void Model::AddOrder(const std::shared_ptr<Order<double>> &order) {
    order_book_->AddOrd(*order);
}

void Model::RemoveOrder(const std::shared_ptr<Order<double>> &order) {
    order_book_->RemoveOrder(*order);
}

Model::Model(const Portfolio &portfolio) :
        portfolio_(std::make_shared<Portfolio>(portfolio)) {

}

double Model::GetMinBuyPrice() {
    return order_book_->GetMinBid();
}

double Model::GetMaxSellPrice() {
    return order_book_->GetMaxAsk();
}

std::shared_ptr<Decision>
Model::MakeDecision(const double prev_sell,
                    const double prev_buy) {
    auto current_sell = GetMaxSellPrice();
    auto current_buy = GetMinBuyPrice();
    auto sell_change_rate = prev_sell / current_sell;
    // if > 1 -> gets cheaper to sell, so that we sell
    auto buy_change_rate = current_buy / prev_buy;
    // if > 1 -> gets expensive to buy -> so we buy
    if (sell_change_rate < 1 && buy_change_rate < 1) {
        // no danger we dont do anyting
        return nullptr;
    }
    if (sell_change_rate > buy_change_rate) {
        //we sell half money
        auto decision = std::make_shared<Decision>(
                std::min(portfolio_->BalanceRub() / 2, (double) order_book_->GetVolume(sell_change_rate)),//amount
                sell_change_rate,// price in rubles
                false // we sell
        );
        portfolio_->CellRubles(decision->amount, decision->price);
        return decision;
    }

    auto decision = std::make_shared<Decision>(
            (portfolio_->BalanceDoll() / 2) * buy_change_rate,//amount
            buy_change_rate,// price in rubles
            true // we buy rubles
    );
    portfolio_->BuyRubles(decision->amount, decision->price);
    return decision;
}
