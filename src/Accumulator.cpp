#include "Accumulator.hpp"

Accumulator Accumulator::operator+= (int i) { 
  value_ += i; 
  return *this;
}

Accumulator Accumulator::operator+= (Accumulator a) { 
  return  *this + a; 
}

Accumulator Accumulator::operator= (int i) { 
  value_ = i; 
  return *this;
}


Accumulator Accumulator::operator+  ( int i) {
  value_ = this->value_ + i; 
  return *this;
}

Accumulator Accumulator::operator+ (Accumulator const& accu) const {
  Accumulator result;
  result.value_ =  value_ + accu.value_;   
  return result;
}

bool Accumulator::operator== (const int & i) {
  return value_ == i; 
}

bool Accumulator::operator< (const int & i) {
  return value_ < i; 
}

//int& Accumulator::operator& () {
//  return value_;
//}




