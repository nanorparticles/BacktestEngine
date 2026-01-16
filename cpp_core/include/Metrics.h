#pragma once
#include <vector>
#include <string>
#include "Event.h"
#include "Portfolio.h"

class Metrics {
    std::vector<double> equity_history_;

public:
    Metrics() = default;

    void record(double equity) {
        equity_history_.push_back(equity);
    }

    double cumulative_return() const;
    double max_drawdown() const;
    double sharpe_ratio(double risk_free_rate = 0.0) const;
    void update(const MarketEvent& e, const Portfolio& portfolio) {
        equity_history_.push_back(portfolio.equity());
    }
    void export_csv(const std::string& filename) const;
};