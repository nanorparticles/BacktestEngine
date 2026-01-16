#pragma once
#include <string>
#include <chrono>

enum class EventType { Market, Order, Fill };

struct Event {
    EventType type;
    long long ts;
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

struct FillEvent : public Event {
    std::string symbol;
    int quantity;
    double fill_price;
    double fee;
};