#include "Asset.h"
#include <chrono>

std::vector<double> Asset::compute_returns() const {
    std::vector<double> returns;
    for (size_t i = 1; i < prices.size(); ++i) {
        returns.push_back((prices[i] - prices[i-1]) / prices[i-1]);
    }
    return returns;
}

std::vector<std::shared_ptr<MarketEvent>> Asset::to_market_events() const {
    std::vector<std::shared_ptr<MarketEvent>> events;
    for (size_t i = 0; i < prices.size(); ++i) {
        auto e = std::make_shared<MarketEvent>();
        e->type = EventType::Market;
        // convert stored timestamp (e.g. time_t or numeric epoch) to a time_point for MarketEvent::ts
        e->ts = std::chrono::system_clock::from_time_t(static_cast<std::time_t>(timestamps[i]));
        e->symbol = symbol;
        e->open = prices[i];
        e->high = prices[i];
        e->low = prices[i];
        e->close = prices[i];
        e->volume = 0;
        events.push_back(e);
    }
    return events;
}
    