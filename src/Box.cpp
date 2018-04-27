#include "Box.hpp"

Box::Box(const Range xRange, const Range yRange) {
  xRange_ = xRange;
  yRange_ = yRange;
}

double Box::width() const {
  return xRange_.length();
}

double Box::height() const {
  return yRange_.length();
}

bool Box::isForward() const {
  return width() >= 0.0;
}

