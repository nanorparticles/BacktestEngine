#pragma once
#include <vector>

class Metrics {
    std::vector<double> equity_history_;
public:
    void record(double equity);
    double cumulative_return() const;
    double max_drawdown() const;
    double sharpe() const;
};