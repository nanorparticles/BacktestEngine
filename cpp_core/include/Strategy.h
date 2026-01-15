#pragma once
#include "Asset.h"

class Strategy {
public:
    int short_window = 5;  // default, can adjust
    int long_window  = 20; // default, can adjust

    double generate_signal(const Asset& asset, int t) const;

private:
    double sma(const std::vector<double>& prices, int t, int window) const;
};