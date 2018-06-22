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
	





