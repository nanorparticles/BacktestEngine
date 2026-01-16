#pragma once
#include "Event.h"
#include "Strategy.h"
#include "Portfolio.h"
#include "Metrics.h"
#include "RiskManager.h"

#include <vector>
#include <memory>

class BacktestEngine {
public:
    void run(std::vector<std::shared_ptr<Event>>& events,
             Strategy& strat,
             Portfolio& portfolio,
             Metrics& metrics,
             RiskManager* risk = nullptr);
};