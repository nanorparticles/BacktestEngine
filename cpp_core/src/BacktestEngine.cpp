#include "BacktestEngine.h"
#include <algorithm>
#include <iostream>

void BacktestEngine::run(
    std::vector<std::shared_ptr<Event>>& events,
    Strategy& strat,
    Portfolio& portfolio,
    Metrics& metrics,
    RiskManager* risk)
{
    // Sort events by timestamp
    std::sort(events.begin(), events.end(),
        [](const std::shared_ptr<Event>& a, const std::shared_ptr<Event>& b){
            return a->ts < b->ts;
        });

    // Event loop
    for (auto& e : events) {
        switch (e->type) {
            case EventType::Market: {
                auto market = std::dynamic_pointer_cast<MarketEvent>(e);
                if (market) {
                    // Apply strategy on market event
                    strat.on_market_event(*market, portfolio);

                    // Update metrics
                    metrics.update(*market, portfolio);

                    // Apply risk management if present
                    if (risk) {
                        // collect order events to pass by reference into the risk manager
                        std::vector<std::shared_ptr<OrderEvent>> order_events;
                        for (const auto& ev : events) {
                            if (ev->type == EventType::Order) {
                                if (auto oe = std::dynamic_pointer_cast<OrderEvent>(ev)) {
                                    order_events.push_back(oe);
                                }
                            }
                        }
                        risk->enforce(order_events, portfolio);
                    }
                }
                break;
            }
            case EventType::Fill: {
                auto fill = std::dynamic_pointer_cast<FillEvent>(e);
                if (fill) {
                    portfolio.apply_fill(*fill);
                }
                break;
            }
            case EventType::Order:
                // Could handle simulated order events here if needed
                break;
        }
    }

    // Export metrics
    metrics.export_csv("../results/results.csv");

    std::cout << "Backtest complete. Final portfolio equity: $"
              << portfolio.equity() << std::endl;
}