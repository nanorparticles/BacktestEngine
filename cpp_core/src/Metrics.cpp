#include "Metrics.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

double Metrics::cumulative_return() const {
    if (equity_history_.empty()) return 0.0;
    return equity_history_.back() / equity_history_.front() - 1.0;
}

double Metrics::max_drawdown() const {
    double max_dd = 0.0;
    double peak = equity_history_.empty() ? 0.0 : equity_history_[0];
    for(double e : equity_history_) {
        if(e > peak) peak = e;
        double dd = (peak - e) / peak;
        if(dd > max_dd) max_dd = dd;
    }
    return max_dd;
}

double Metrics::sharpe_ratio(double risk_free_rate) const {
    if(equity_history_.size() < 2) return 0.0;
    std::vector<double> returns;
    returns.reserve(equity_history_.size() - 1);
    for(size_t i = 1; i < equity_history_.size(); ++i) {
        returns.push_back((equity_history_[i] - equity_history_[i-1]) / equity_history_[i-1] - risk_free_rate);
    }
    double mean = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double sq_sum = 0.0;
    for(double r : returns) sq_sum += (r - mean)*(r - mean);
    double stddev = std::sqrt(sq_sum / (returns.size() - 1));
    return stddev == 0.0 ? 0.0 : mean / stddev * std::sqrt(252); // Annualized Sharpe
}

void Metrics::export_csv(const std::string& filename) const {
    std::ofstream out(filename);
    if(!out.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }
    out << "TimeStep,Equity\n";
    for(size_t i = 0; i < equity_history_.size(); ++i) {
        out << i << "," << equity_history_[i] << "\n";
    }
    out.close();
    std::cout << "Metrics exported to " << filename << "\n";
}