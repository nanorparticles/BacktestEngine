#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Event.h"

class Asset {
public:
    std::string symbol;
    std::vector<double> prices;
    std::vector<long long> timestamps;

    std::vector<double> compute_returns() const;
    std::vector<std::shared_ptr<MarketEvent>> to_market_events() const;
};