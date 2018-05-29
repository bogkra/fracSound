#pragma once
#include "Incrementator.hpp"

class Accumulator : Incrementator {
public:
  Accumulator operator+= (int i);
  Accumulator operator+= (Accumulator a);
  Accumulator operator=  (int  i);
  Accumulator operator+  (int i);
  Accumulator operator+ (Accumulator const& accu) const;
  friend Accumulator operator+ (int i, Accumulator accu) {
    return accu + i;
  };
  bool operator== (const int & i);
  bool operator< (const int & i);
  int getValue() const {return value_;};
};






