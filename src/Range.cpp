#include "Range.hpp"

Range::Range(const double begin, const double end) {
  begin_ = begin;
  end_ = end;
}

double Range::length() const {
  return end_ - begin_;
}

bool Range::isForward() const {
  return length() >= 0;
}


	





