#pragma once
#include <vector>
#include <string>
#include <unordered_map>

struct Trade {
    std::string symbol;
    double price;
    int quantity; // +ve = buy, -ve = sell
};

class BacktestEngine {
public:
    BacktestEngine(double initial_cash);
    void loadHistoricalData(const std::string& filename);
    void placeTrade(const Trade& trade);
    void runStrategy(); // implement strategy logic
    void exportResults(const std::string& filename);

private:
    double cash;
    std::unordered_map<std::string, int> positions;
    std::unordered_map<std::string, std::vector<double>> historical_prices;
    std::vector<Trade> trade_log;
};