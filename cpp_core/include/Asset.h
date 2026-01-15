#pragma once
#include <string>
#include <vector>

struct Asset {
    std::string symbol;
    std::vector<double> prices;
    std::vector<double> returns;

    void compute_returns();
};