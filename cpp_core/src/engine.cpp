#include "engine.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

BacktestEngine::BacktestEngine(double initial_cash) : cash(initial_cash) {}

void BacktestEngine::loadHistoricalData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Derive a symbol name from the filename (e.g. ../data/AAPL_av.csv -> AAPL)
    std::string sym = filename;
    auto pos = sym.find_last_of("/\\");
    if (pos != std::string::npos) sym = sym.substr(pos + 1);
    // remove extension
    auto dot = sym.find('.');
    if (dot != std::string::npos) sym = sym.substr(0, dot);
    // if there is a suffix like _av, take the part before it
    auto us = sym.find('_');
    if (us != std::string::npos) sym = sym.substr(0, us);

    std::string line;
    // skip header line if present
    if (!std::getline(file, line)) return;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> cols;
        while (std::getline(ss, token, ',')) cols.push_back(token);
        // expect at least: date, open, high, low, close, ...
        if (cols.size() < 5) continue;
        double close_price = 0.0;
        try {
            close_price = std::stod(cols[4]);
        } catch (...) {
            continue;
        }
        historical_prices[sym].push_back(close_price);
    }
}

void BacktestEngine::placeTrade(const Trade& trade) {
    double cost = trade.price * trade.quantity;
    std::cout << "Attempting trade: " << trade.symbol 
              << " Qty: " << trade.quantity 
              << " Price: " << trade.price 
              << " Cash: " << cash << std::endl;

    if (cash - cost < 0) {
        std::cerr << "Not enough cash for trade\n";
        return;
    }
    cash -= cost;
    positions[trade.symbol] += trade.quantity;
    trade_log.push_back(trade);
}

void BacktestEngine::runStrategy() {
    // Example: simple moving average crossover
    for (auto& kv : historical_prices) {
        const auto& prices = kv.second;
        int n = prices.size();
        std::cout << "Loaded " << prices.size() << " prices for " << kv.first << "\n";
        for (int i = 5; i < n; ++i) { // 5-day SMA example
            double sma = 0;
            for (int j = i-5; j<i; ++j) sma += prices[j];
            sma /= 5;
            if (prices[i] > sma) placeTrade({kv.first, prices[i], 10});
            else placeTrade({kv.first, prices[i], -10});
        }
    }
}

void BacktestEngine::exportResults(const std::string& filename) {
    std::ofstream out(filename);
    out << "symbol,price,quantity\n";
    for (auto& t : trade_log) {
        out << t.symbol << "," << t.price << "," << t.quantity << "\n";
    }
}