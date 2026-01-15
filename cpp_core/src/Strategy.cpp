#include "Strategy.h"
#include <numeric>
#include <algorithm>

// ---------------------------
// Helper: simple moving average
// ---------------------------
double Strategy::sma(const std::vector<double>& prices, int t, int window) const {
    if (t + 1 < window || window <= 0) return 0.0;

    double sum = 0.0;
    for (int i = t - window + 1; i <= t; ++i) {
        sum += prices[i];
    }
    return sum / window;
}

// ---------------------------
// Default: SMA Crossover
// ---------------------------
double Strategy::generate_signal(const Asset& asset, int t) const {
    if (t < long_window) return 0.0; // Not enough data

    double short_sma = sma(asset.prices, t, short_window);
    double long_sma  = sma(asset.prices, t, long_window);

    if (short_sma > long_sma) return 1.0;   // Go long
    else if (short_sma < long_sma) return -1.0; // Go short
    else return 0.0; // Flat
}