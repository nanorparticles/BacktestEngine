#pragma once
#include <vector>
#include "Asset.h"
#include "Strategy.h"
#include "Portfolio.h"
#include "RiskManager.h"
#include <string>

class BacktestEngine {
public:
    void run(
        const std::vector<Asset>& assets,
        Strategy& strategy,
        const std::string& output_csv = "results.csv"
    );
};