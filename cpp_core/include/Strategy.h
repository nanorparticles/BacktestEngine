#pragma once
#include "Event.h"
#include <vector>
#include <memory>

class Strategy {
public:
    virtual std::vector<std::shared_ptr<OrderEvent>> on_market_event(const MarketEvent& e) = 0;
    virtual ~Strategy() = default;
};