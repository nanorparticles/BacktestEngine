#include "Metrics.h"
#include <cmath>
#include <algorithm>
#include <numeric>

namespace Metrics {

double mean(const std::vector<double>& x) {
    if (x.empty()) return 0.0;
    return std::accumulate(x.begin(), x.end(), 0.0) / x.size();
}

double stddev(const std::vector<double>& x) {
    if (x.size() < 2) return 0.0;

    double m = mean(x);
    double accum = 0.0;

    for (double v : x) {
        double diff = v - m;
        accum += diff * diff;
    }

    return std::sqrt(accum / (x.size() - 1));  // sample std dev
}

double sharpe_ratio(
    const std::vector<double>& returns,
    double risk_free_rate,
    double annualization_factor
) {
    if (returns.size() < 2) return 0.0;

    // Excess returns
    std::vector<double> excess(returns.size());
    for (size_t i = 0; i < returns.size(); ++i) {
        excess[i] = returns[i] - risk_free_rate / annualization_factor;
    }

    double mu = mean(excess);
    double sigma = stddev(excess);

    if (sigma == 0.0) return 0.0;

    return std::sqrt(annualization_factor) * mu / sigma;
}

double cumulative_return(const std::vector<double>& returns) {
    double cumulative = 1.0;
    for (double r : returns) {
        cumulative *= (1.0 + r);
    }
    return cumulative - 1.0;
}

double max_drawdown(const std::vector<double>& returns) {
    double peak = 1.0;
    double equity = 1.0;
    double max_dd = 0.0;

    for (double r : returns) {
        equity *= (1.0 + r);
        peak = std::max(peak, equity);
        double drawdown = (peak - equity) / peak;
        max_dd = std::max(max_dd, drawdown);
    }

    return max_dd;
}

}