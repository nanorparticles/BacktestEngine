#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

Asset load_asset_csv(const std::string& symbol, const std::string& path) {
    Asset a;
    a.symbol = symbol;

    std::ifstream file(path);
    if(!file.is_open()) throw std::runtime_error("Could not open CSV: " + path);

    std::string line;
    bool header_skipped = false;

    while(std::getline(file, line)) {
        if(!header_skipped) { header_skipped = true; continue; } // skip header
        std::stringstream ss(line);
        std::string ts_str, price_str;

        if(!std::getline(ss, ts_str, ',')) continue;
        if(!std::getline(ss, price_str, ',')) continue;

        long long ts = std::stoll(ts_str);
        double price = std::stod(price_str);

        a.timestamps.push_back(ts);
        a.prices.push_back(price);
    }

    return a;
}