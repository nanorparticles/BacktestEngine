#pragma once
#include "Event.h"
#include <queue>
#include <memory>

struct EventCompare {
    bool operator()(const std::shared_ptr<Event>& a,
                    const std::shared_ptr<Event>& b) const {
        return a->ts > b->ts; // min-heap: earliest event first
    }
};

class EventQueue {
private:
    std::priority_queue<std::shared_ptr<Event>,
                        std::vector<std::shared_ptr<Event>>,
                        EventCompare> queue;
public:
    void push(std::shared_ptr<Event> e);
    std::shared_ptr<Event> pop();
    bool empty() const;
};