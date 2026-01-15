#include "RiskManager.h"
#include <numeric>
#include <cmath>

void RiskManager::enforce(std::vector<Asset>& assets, Portfolio& portfolio) {

    size_t N = assets.size();
    std::vector<double> vols(N, 0.0);

    // 1. Compute asset volatilities (daily stddev of returns)
    for (size_t i = 0; i < N; ++i) {
        double mean_ret = std::accumulate(
            assets[i].returns.begin(),
            assets[i].returns.end(), 0.0
        ) / assets[i].returns.size();

        double accum = 0.0;
        for (double r : assets[i].returns) {
            accum += (r - mean_ret) * (r - mean_ret);
        }
        vols[i] = std::sqrt(accum / (assets[i].returns.size() - 1));
    }

    // 2. Scale weights inversely proportional to volatility
    double weight_sum = 0.0;
    for (size_t i = 0; i < N; ++i) {
        if (vols[i] > 0.0)
            portfolio.weights[i] /= vols[i];
        weight_sum += std::abs(portfolio.weights[i]);
    }

    // 3. Normalize weights to max leverage
    if (weight_sum > max_leverage) {
        double scale = max_leverage / weight_sum;
        for (size_t i = 0; i < N; ++i) {
            portfolio.weights[i] *= scale;
        }
    }
}