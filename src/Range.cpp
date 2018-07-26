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

bool Range::isBetween(const double & x) {
  return (begin_ <= x and x <= end_)   or
         (end_   <= x and x <= begin_);
}

bool Range::intoBoundaries(double & x) {
  if (not isBetween(x)) {
    x = std::max(x, min());
    x = std::min(x, max());
    return true;
  }    
  return false;
}

double Range::proportionallyBetween(const double & alpha) {
  return begin_ + alpha * length();
}

void Range::rescale(Range outside) { 
  begin_ = outside.proportionallyBetween(begin_);
  end_   = outside.proportionallyBetween(end_);
}

void Range::rescale(const double & alpha) { 
  begin_ *= alpha;
  end_ *= alpha;
}

void Range::moveDown() {
  end_ -= begin_;
  begin_ = 0;
}

bool in(const double & x, Range & range) {
  return range.isBetween(x);
}

void Range::move(const double & x) {
  end_ += x;
  begin_ += x;
}




