#pragma once
#include <string>
#include <chrono>

enum class EventType { Market, Order, Fill };

struct Event {
    EventType type;
    std::chrono::system_clock::time_point ts;

    virtual ~Event() = default;  // <-- make it polymorphic
};
struct MarketEvent : public Event {
    std::string symbol;
    double open, high, low, close;
    double volume;
};

struct OrderEvent : public Event {
    std::string symbol;
    int quantity;
    double limit_price;
};

struct FillEvent : Event {
    std::string symbol;
    int quantity;
    double fill_price;
    double fee;

    FillEvent(const std::string& sym, int qty, double price, double f = 0.0)
        : symbol(sym), quantity(qty), fill_price(price), fee(f) {}
};