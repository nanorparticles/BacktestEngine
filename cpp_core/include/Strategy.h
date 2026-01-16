#pragma once
#include "Event.h"
#include "Portfolio.h"

// Base abstract class
class Strategy {
public:
    virtual ~Strategy() = default;

    // Override this in derived classes
    virtual void on_market_event(const MarketEvent& e, Portfolio& portfolio) = 0;
};