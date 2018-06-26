#include "Range.hpp"
#include <algorithm>

double Range::length() const {
  return end_ - begin_;
}

bool Range::isForward() const {
  return length() >= 0;
}

double Range::min() const {
  return std::min(begin_, end_);
}

double Range::max() const {
  return std::max(begin_, end_);
}

bool Range::isBetween(const double x) {
  return (begin_ >= x and x<= end_) or
         (end_   >= x and x<= begin_);
}

double Range::proportionallyBetween(const double alpha) {
  return begin_ + alpha * (end_ - begin_);
}

void Range::rescale(Range outside) { 
  begin_ = outside.proportionallyBetween(begin_);
  end_   = outside.proportionallyBetween(end_);
}





