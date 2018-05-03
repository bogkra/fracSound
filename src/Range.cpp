#include "Range.hpp"

double Range::length() const {
  return end_ - begin_;
}

bool Range::isForward() const {
  return length() >= 0;
}


	





