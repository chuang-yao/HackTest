#include "ht/Event/Event.hpp"

#include <iostream>

namespace HackTest {

Event::Event(Type t) : type_(t), time_(std::chrono::system_clock::now()) {}

Event::Event(Type t, EventQueue &q)
    : type_(t), time_(std::chrono::system_clock::now()) {
  q.queue_.push(*this);
}

void Event::show_datetime() const {
  auto t = std::chrono::system_clock::to_time_t(time_);
  std::cout << std::ctime(&t);
}

Event::Type Event::get_type() const { return type_; }

std::ostream &operator<<(std::ostream &os, const Event &e) {
  switch (e.type_) {
  case Event::Type::MKT:
    os << "MKT\t";
    break;
  case Event::Type::FIL:
    os << "FIL\t";
    break;
  case Event::Type::ORD:
    os << "ORD\t";
    break;
  case Event::Type::SIG:
    os << "SIG\t";
    break;
  }
  e.show_datetime();
  return os;
}

void EventQueue::show() const {
  auto q = queue_;
  while (!q.empty()) {
    std::cout << q.front();
    q.pop();
  }
}

bool EventQueue::empty() const { return queue_.empty(); }

Event EventQueue::get_event() {
  auto event{queue_.back()};
  queue_.pop();
  return event;
}

} // namespace HackTest
