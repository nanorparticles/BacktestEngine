#pragma once
#include "Event.h"
#include <unordered_map>
#include <string>

class Portfolio {
    std::unordered_map<std::string, int> positions_;
    double cash_;
public:
    Portfolio(double initial_cash);
    double cash() const { return cash_; }
    void buy(const std::string& symbol, int quantity, double price);
    void sell(const std::string& symbol, int quantity, double price);
    void apply_fill(const FillEvent& e);
    void mark_to_market(const MarketEvent& e);
    double equity() const;
    int position(const std::string& symbol) const;
};