#include "BacktestEngine.h"
#include "BuyAndHoldStrategy.h"
#include "CSVLoader.h"   // implement load_asset_csv
#include "Metrics.h"
#include "Portfolio.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<std::string> symbols = {"AAPL", "GOOG", "MSFT"};
    std::vector<std::string> paths = {
        "../data/AAPL_av.csv",
        "../data/GOOG_av.csv",
        "../data/MSFT_av.csv"
    };

    std::vector<std::shared_ptr<Event>> events;
    std::vector<Asset> assets;
    for(size_t i = 0; i < symbols.size(); ++i) {
        assets.push_back(load_asset_csv(symbols[i], paths[i]));
        auto market_events = assets.back().to_market_events();
        for(auto& e : market_events) events.push_back(e);
    }

    Portfolio portfolio(100000.0);
    BuyAndHoldStrategy strat;
    Metrics metrics;
    BacktestEngine engine;

    engine.run(events, strat, portfolio, metrics);

    return 0;
}