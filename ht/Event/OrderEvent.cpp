#include "ht/Event/OrderEvent.hpp"

#include <iostream>

namespace HackTest {

OrderEvent::OrderEvent(EventQueue &q, std::string symbol, std::string order,
                       uint32_t quantity, std::string direction)
    : Event(Type::ORD), symbol_(std::move(symbol)), order_(std::move(order)),
      quantity_(quantity), direction_(std::move(direction)) {}

void OrderEvent::print_order() const {
  std::cout << symbol_ << '\t' << order_ << '\t' << quantity_ << '\t'
            << direction_ << '\n';
}

std::string OrderEvent::get_symbol() const { return symbol_; }

uint32_t OrderEvent::get_quantity() const { return quantity_; }

std::string OrderEvent::get_direction() const { return direction_; }

} // namespace HackTest
