#include "Portfolio.h"
#include <numeric>
#include <cmath>

Portfolio::Portfolio(int n_assets)
    : weights(n_assets, 0.0), cash(1.0) {}

double Portfolio::total_exposure() const {
    return std::accumulate(
        weights.begin(), weights.end(), 0.0,
        [](double a, double b) { return a + std::abs(b); }
    );
}