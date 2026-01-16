#include "Portfolio.h"

Portfolio::Portfolio(double initial_cash) : cash_(initial_cash) {}

void Portfolio::buy(const std::string& symbol, int quantity, double price) {
    cash_ -= quantity * price;
    positions_[symbol] += quantity;
}

void Portfolio::sell(const std::string& symbol, int quantity, double price) {
    cash_ += quantity * price;
    positions_[symbol] -= quantity;
}

void Portfolio::apply_fill(const FillEvent& e) {
    if (e.quantity > 0) buy(e.symbol, e.quantity, e.fill_price + e.fee);
    else sell(e.symbol, -e.quantity, e.fill_price - e.fee);
}

void Portfolio::mark_to_market(const MarketEvent& e) {
    // optional: update portfolio value based on current market price
}

double Portfolio::equity() const {
    double eq = cash_;
    for (const auto& [sym, qty] : positions_) {
        // Mark-to-market requires a price feed; for now assume qty * some price
    }
    return eq;
}

int Portfolio::position(const std::string& symbol) const {
    auto it = positions_.find(symbol);
    return it != positions_.end() ? it->second : 0;
}

