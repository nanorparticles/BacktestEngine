#pragma once
#include "Portfolio.h"
#include "Asset.h"
#include <vector>

class RiskManager {
public:
    double max_leverage = 1.0;            // Max total portfolio exposure
    double target_volatility = 0.02;      // Target daily vol per portfolio (~2%)

    void enforce(std::vector<Asset>& assets, Portfolio& portfolio);
};