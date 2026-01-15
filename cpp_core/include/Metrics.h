#pragma once

#include <vector>

namespace Metrics {

    double mean(const std::vector<double>& x);

    double stddev(const std::vector<double>& x);

    double sharpe_ratio(
        const std::vector<double>& returns,
        double risk_free_rate = 0.0,
        double annualization_factor = 252.0
    );

    double cumulative_return(const std::vector<double>& returns);

    double max_drawdown(const std::vector<double>& returns);

}