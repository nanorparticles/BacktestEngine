#include "BuyAndHoldStrategy.h"
#include <memory>

std::vector<std::shared_ptr<OrderEvent>> BuyAndHoldStrategy::on_market_event(const MarketEvent& e) {
    std::vector<std::shared_ptr<OrderEvent>> orders;
    static bool bought = false;
    if (!bought) {
        auto order = std::make_shared<OrderEvent>();
        order->type = EventType::Order;
        order->ts = e.ts;
        order->symbol = e.symbol;
        order->quantity = 1;
        order->limit_price = 0.0;
        orders.push_back(order);
        bought = true;
    }
    return orders;
}