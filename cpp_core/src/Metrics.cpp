#include "Metrics.h"
#include <numeric>
#include <cmath>
#include <algorithm>

void Metrics::record(double equity) {
    equity_history_.push_back(equity);
}

double Metrics::cumulative_return() const {
    if (equity_history_.empty()) return 0.0;
    return (equity_history_.back() - equity_history_.front()) / equity_history_.front();
}

double Metrics::max_drawdown() const {
    double max_dd = 0.0, peak = -1e9;
    for (auto e : equity_history_) {
        peak = std::max(peak, e);
        max_dd = std::max(max_dd, (peak - e) / peak);
    }
    return max_dd;
}

double Metrics::sharpe() const {
    if (equity_history_.size() < 2) return 0.0;
    std::vector<double> returns;
    for (size_t i = 1; i < equity_history_.size(); ++i)
        returns.push_back(equity_history_[i] - equity_history_[i-1]);
    double mean = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double stddev = 0.0;
    for (auto r : returns) stddev += (r - mean)*(r - mean);
    stddev = std::sqrt(stddev / (returns.size() - 1));
    return stddev > 0 ? mean / stddev : 0.0;
}