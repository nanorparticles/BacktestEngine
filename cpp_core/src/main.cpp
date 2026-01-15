#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Asset.h"
#include "Strategy.h"
#include "BacktestEngine.h"
#include "Metrics.h"

// Helper: load CSV (assumes first column = close prices, header present)
// Helper: load CSV (expects columns: date, open, high, low, close, ...)
Asset load_asset_csv(const std::string& filepath, const std::string& symbol) {
    Asset asset;
    asset.symbol = symbol;
    std::ifstream file(filepath);
    std::string line;

    // Skip header
    if (!std::getline(file, line)) return asset;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> cols;
        while (std::getline(ss, token, ',')) cols.push_back(token);
        // expect at least 5 columns: date, open, high, low, close
        if (cols.size() < 5) continue;
        try {
            double close = std::stod(cols[4]);
            asset.prices.push_back(close);
        } catch (...) {
            continue;
        }
    }

    asset.compute_returns();
    return asset;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " asset1.csv asset2.csv ...\n";
        return 1;
    }

    std::vector<Asset> assets;

    // Load assets dynamically from command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string filepath = argv[i];
        // Extract symbol from filename (strip .csv)
        size_t slash = filepath.find_last_of("/\\");
        size_t dot = filepath.find_last_of(".");
        std::string symbol = filepath.substr(slash + 1, dot - slash - 1);
        assets.push_back(load_asset_csv(filepath, symbol));
    }

    // Strategy
    Strategy sma_strategy;
    sma_strategy.short_window = 5;
    sma_strategy.long_window  = 20;

    // Run backtest
    BacktestEngine engine;
    engine.run(assets, sma_strategy, "results.csv");

    // Read results.csv to compute portfolio metrics
    std::ifstream infile("results.csv");
    if (!infile.is_open()) {
        std::cerr << "Failed to open results.csv\n";
        return 1;
    }

    std::string line;
    std::vector<double> portfolio_returns;

    // Skip header
    std::getline(infile, line);

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string day, pnl;
        std::getline(ss, day, ',');
        std::getline(ss, pnl, ',');
        portfolio_returns.push_back(std::stod(pnl));
    }

    double sharpe = Metrics::sharpe_ratio(portfolio_returns);
    double cum_ret = Metrics::cumulative_return(portfolio_returns);
    double mdd = Metrics::max_drawdown(portfolio_returns);

    std::cout << "Portfolio Metrics:\n";
    std::cout << "Sharpe Ratio: " << sharpe << "\n";
    std::cout << "Cumulative Return: " << cum_ret * 100 << "%\n";
    std::cout << "Max Drawdown: " << mdd * 100 << "%\n";

    return 0;
}