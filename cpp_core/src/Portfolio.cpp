#include "Portfolio.h"

Portfolio::Portfolio(double initial_cash) : cash_(initial_cash) {}

void Portfolio::apply_fill(const FillEvent& e) {
    positions_[e.symbol] += e.quantity;
    cash_ -= e.quantity * e.fill_price + e.fee;
}

void Portfolio::mark_to_market(const MarketEvent& e) {
    // Placeholder
}

double Portfolio::equity() const {
    double eq = cash_;
    for (const auto& [sym, qty] : positions_) {
        eq += qty * 1.0; // placeholder for current price
    }
    return eq;
}