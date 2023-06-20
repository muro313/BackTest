#pragma once

#include <cstddef>
#include <chrono>
#include <stdexcept>

template<typename PriceType>
class Order {
public:
    explicit Order(const PriceType &price,
                   size_t volume = 0,
                   bool is_ask = true,
                   std::chrono::time_point<std::chrono::system_clock> created
                   = std::chrono::system_clock::now(),
                   std::chrono::time_point<std::chrono::system_clock> end
                   = std::chrono::system_clock::now()
    ) : price_(price),
        volume_(volume),
        is_ask_(is_ask),
        creation_time_(created),
        end_time_(end) {

    };

    PriceType GetPrice() const {
        return price_;
    }

    size_t GetVolume() const {
        return volume_;
    }

    bool IsAsk() const {
        return is_ask_;
    }

    bool IsBid() const {
        return !is_ask_;
    }

    bool Exists() const {
        return std::chrono::system_clock::now() < end_time_
               && std::chrono::system_clock::now() > creation_time_;
    }

    void IncreaseVolume(size_t volume) {
        volume_ += volume;
    }

    void DecreaseVolume(size_t volume) {
        if (volume > volume_) {
            throw std::runtime_error("Not enough volume");
        }
        volume_ -= volume;
    }

    void ChangeType() {
        is_ask_ = !is_ask_;
    }

    void IncreaseLife(const std::chrono::system_clock::duration &time) {
        end_time_ += time;
    }

private:
    PriceType price_;
    size_t volume_ = 0;
    bool is_ask_;
    std::chrono::time_point<std::chrono::system_clock> creation_time_;
    std::chrono::time_point<std::chrono::system_clock> end_time_;
};
