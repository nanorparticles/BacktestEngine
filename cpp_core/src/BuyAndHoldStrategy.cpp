#include "BuyAndHoldStrategy.h"
#include "Portfolio.h"
#include <iostream>

void BuyAndHoldStrategy::on_market_event(const MarketEvent& e, Portfolio& portfolio) {
    if (portfolio.position(e.symbol) == 0) {
        // Buy as much as possible, but spread across all symbols
        double total_cash = portfolio.cash();
        size_t remaining_symbols = 3; // or dynamically count symbols with position 0
        int qty = static_cast<int>(total_cash / remaining_symbols / e.close);
        if (qty > 0) {
            portfolio.buy(e.symbol, qty, e.close);
            std::cout << "BuyAndHold: Bought " << qty << " of " << e.symbol << " at $" << e.close << "\n";
        }
    }
}