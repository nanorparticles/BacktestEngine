#pragma once
#include "Strategy.h"

class BuyAndHoldStrategy : public Strategy {
public:
    std::vector<std::shared_ptr<OrderEvent>> on_market_event(const MarketEvent& e) override;
};