#include "BacktestEngine.h"
#include <memory>

void BacktestEngine::run(EventQueue& eq, Strategy& strat, Portfolio& port, Metrics& metrics, RiskManager* rm) {
    while (!eq.empty()) {
        auto event = eq.pop();
        if (!event) continue;

        if (event->type == EventType::Market) {
            auto market = std::static_pointer_cast<MarketEvent>(event);

            auto orders = strat.on_market_event(*market);
            if (rm) rm->enforce(orders, port);

            for (auto& o : orders) {
                FillEvent fill;
                fill.type = EventType::Fill;
                fill.ts = o->ts;
                fill.symbol = o->symbol;
                fill.quantity = o->quantity;
                fill.fill_price = market->close;
                fill.fee = 0.0;
                port.apply_fill(fill);
            }

            port.mark_to_market(*market);
            metrics.record(port.equity());
        }
    }
}