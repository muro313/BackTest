#pragma once

#include <map>
#include "vector"
#include "Order.h"
#include <memory>


template<typename PriceType>
class OrderBook {
    using OrderPtr = std::shared_ptr<Order<PriceType>>;
public:
    OrderBook() = default;

    explicit OrderBook(const std::vector<Order<PriceType>> &ords) {
        for (const auto &ord: ords) {
            AddOrd(ord);
        }
    }

    PriceType GetMaxAsk() {
        if(AskAmount() == 0){
            throw std::runtime_error("No any ask to get max");
        }
        auto iter = orders_.begin();
        std::advance(iter, asks_count_ - 1);
        return iter->first;;
    }

    PriceType GetMinBid() {
        if(BidAmount() == 0){
            throw std::runtime_error("No bid ask to get min");
        }
        auto iter = orders_.begin();
        std::advance(iter, asks_count_);
        return iter->first;;
    }

    PriceType BidAskSpread() {
        return GetMinBid() - GetMaxAsk();
    }

    void AddOrd(const Order<PriceType> &new_ord) {
        auto it = orders_.find(new_ord.GetPrice());
        if (it == orders_.end()) {
            orders_.insert(std::make_pair(
                    new_ord.GetPrice(),
                    std::make_shared<Order<PriceType>>(new_ord)
            ));
            if (new_ord.IsAsk()) {
                ++asks_count_;
            }
            return;
        }
        it->second->IncreaseVolume(new_ord.GetVolume());
    }


    void RemoveOrder(const Order<PriceType> &order) {
        auto it = orders_.find(order.GetPrice());
        if (it == orders_.end()) {
            throw std::runtime_error("No such order to remove");
        }
        if (it->second->GetVolume() < order.GetVolume()) {
            throw std::runtime_error("Not enough order to remove");
        }
        it->second->DecreaseVolume(order.GetVolume());
        if (it->second->GetVolume() == 0) {
            if (it->second->IsAsk()) {
                --asks_count_;
            }
            orders_.erase(it);
        }
    }

    size_t BidAmount() const {
        return orders_.size() - asks_count_;
    }

    size_t AskAmount() const {
        return asks_count_;
    }

    size_t GetVolume(PriceType price){
        auto iter = orders_.find(price);
        if(iter == orders_.end()){
            return 0;
        }
        return iter->second->GetVolume();
    }
private:
    size_t asks_count_ = 0;
    std::map<PriceType, OrderPtr> orders_;
};



