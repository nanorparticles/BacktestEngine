#include "Asset.h"
#include "EventQueue.h"
#include "BacktestEngine.h"
#include "Portfolio.h"
#include "Metrics.h"
#include "RiskManager.h"
#include "BuyAndHoldStrategy.h"

#include <iostream>

int main() {
    Asset aapl;
    aapl.symbol = "AAPL";
    aapl.prices = {150, 152, 151, 153, 155};
    aapl.timestamps = {1,2,3,4,5};

    EventQueue eq;
    for (auto e : aapl.to_market_events()) eq.push(e);

    Portfolio port(10000.0);
    Metrics metrics;
    RiskManager rm;
    BuyAndHoldStrategy strat;
    BacktestEngine engine;

    engine.run(eq, strat, port, metrics, &rm);

    std::cout << "Equity: " << port.equity() << "\n";
    std::cout << "Cumulative Return: " << metrics.cumulative_return() << "\n";
    std::cout << "Max Drawdown: " << metrics.max_drawdown() << "\n";
    std::cout << "Sharpe Ratio: " << metrics.sharpe() << "\n";
}