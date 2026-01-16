#include "EventQueue.h"

void EventQueue::push(std::shared_ptr<Event> e) {
    queue.push(e);
}

std::shared_ptr<Event> EventQueue::pop() {
    if(queue.empty()) return nullptr;
    auto e = queue.top();
    queue.pop();
    return e;
}

bool EventQueue::empty() const {
    return queue.empty();
}