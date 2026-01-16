#pragma once
#include <string>
#include <chrono>
#include <variant>

// --- Event Types ---
enum class EventType {
    Market,
    Order,
    Fill
};

// Base Event struct
struct Event {
    EventType type;
    std::chrono::system_clock::time_point ts;
    virtual ~Event() = default;
};

// Market Event
struct MarketEvent : Event {
    std::string symbol;
    double open, high, low, close, volume;
};

// Order Event
struct OrderEvent : Event {
    std::string symbol;
    int quantity;
    double limit_price;  // 0 means market
};

// Fill Event
struct FillEvent : Event {
    std::string symbol;
    int quantity;
    double fill_price;
    double fee;
};