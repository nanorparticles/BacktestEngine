#pragma once
#include "EventQueue.h"
#include "Portfolio.h"
#include "Metrics.h"
#include "Strategy.h"
#include "RiskManager.h"

class BacktestEngine {
public:
    void run(EventQueue& eq, Strategy& strat, Portfolio& port, Metrics& metrics, RiskManager* rm=nullptr);
};