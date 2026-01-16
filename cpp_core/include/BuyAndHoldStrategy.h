#pragma once
#include "Strategy.h"
#include <unordered_map>
#include <string>

class BuyAndHoldStrategy : public Strategy {
    std::unordered_map<std::string, bool> has_bought_;
public:
    BuyAndHoldStrategy() = default;

    void on_market_event(const MarketEvent& e, Portfolio& portfolio) override;
};