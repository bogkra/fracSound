#include "Incrementator.hpp"


Incrementator& Incrementator::operator++ () { 
  value_++; 
  return *this;
}

Incrementator Incrementator::operator++ (int) { 
  ++value_;
  return *this;
}

bool Incrementator::times(const int end) {
  return value_++ < end;
}


