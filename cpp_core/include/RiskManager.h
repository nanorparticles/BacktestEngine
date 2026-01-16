#pragma once
#include "Portfolio.h"
#include "Event.h"
#include <vector>
#include <memory>

class RiskManager {
public:
    void enforce(std::vector<std::shared_ptr<OrderEvent>>& orders, const Portfolio& portfolio);
};