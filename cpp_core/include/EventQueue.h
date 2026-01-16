#pragma once
#include "Event.h"
#include <queue>
#include <memory>
#include <vector>

struct EventCompare {
    bool operator()(const std::shared_ptr<Event>& a, const std::shared_ptr<Event>& b) {
        return a->ts > b->ts; // min-heap by timestamp
    }
};

class EventQueue {
    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventCompare> pq_;
public:
    void push(std::shared_ptr<Event> e);
    std::shared_ptr<Event> pop();
    bool empty() const;
};