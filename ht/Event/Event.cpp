//
// Created by Chuang Yao on 11/04/2021.
//

#include "ht/Event/Event.hpp"

#include <iostream>

namespace HackTest {

Event::Event(Type t) : type_(t), time_(std::chrono::system_clock::now()) {}

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
  auto q{queue_};
  while (!q.empty()) {
    std::cout << *(q.front());
    q.pop();
  }
}

bool EventQueue::is_empty() const { return queue_.empty(); }

std::shared_ptr<Event> EventQueue::get_event_handle() {
  std::shared_ptr<Event> p{std::move(queue_.front())};
  queue_.pop();
  return p;
}

void EventQueue::push(const std::shared_ptr<Event> &e) { queue_.push(e); }

} // namespace HackTest
