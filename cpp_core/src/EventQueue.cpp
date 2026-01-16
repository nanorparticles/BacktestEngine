#include "EventQueue.h"

void EventQueue::push(std::shared_ptr<Event> e) {
    pq_.push(e);
}

std::shared_ptr<Event> EventQueue::pop() {
    if (pq_.empty()) return nullptr;
    auto e = pq_.top();
    pq_.pop();
    return e;
}

bool EventQueue::empty() const {
    return pq_.empty();
}