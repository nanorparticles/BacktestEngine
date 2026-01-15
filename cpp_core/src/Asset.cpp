#include "Asset.h"
#include <cmath>

void Asset::compute_returns() {
    returns.clear();
    returns.reserve(prices.size());

    if (prices.empty()) return;

    // First return = 0 (no prior price)
    returns.push_back(0.0);

    for (size_t i = 1; i < prices.size(); ++i) {
        double prev = prices[i - 1];
        double curr = prices[i];

        if (prev <= 0.0) {
            returns.push_back(0.0);
        } else {
            returns.push_back((curr - prev) / prev);
        }
    }
}