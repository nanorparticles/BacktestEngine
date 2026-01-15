#pragma once
#include <vector>

class Portfolio {
public:
    std::vector<double> weights;   // per asset
    double cash;

    Portfolio(int n_assets);

    double total_exposure() const;
};