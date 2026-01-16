#pragma once
#include "Event.h"
#include <unordered_map>
#include <string>

class Portfolio {
    std::unordered_map<std::string, int> positions_;
    double cash_;
public:
    Portfolio(double initial_cash);
    void apply_fill(const FillEvent& e);
    void mark_to_market(const MarketEvent& e);
    double equity() const;
};