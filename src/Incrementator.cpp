#include "Incrementator.hpp"


Incrementator& Incrementator::operator++ () { 
  value_++; 
  return *this;
}

Incrementator Incrementator::operator++ (int) { 
  ++value_;
  return *this;
}

bool Incrementator::repeat(const int end) {
  return value_++ < end;
}


void operator * (const int upperBound, std::function<void (void)> repeatedFunction) {
   for (int i = 0; i < upperBound; i++) repeatedFunction();
}


void operator * (const int upperBound, std::function<void (const int)> repeatedFunction) {
   for (int i = 0; i < upperBound; i++) repeatedFunction(i);
}
