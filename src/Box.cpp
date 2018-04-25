#include "Box.hpp"

Box::Box(const double x1, const double x2, const double y1, const double y2) {
  x1_ = x1;
  x2_ = x2;
  y1_ = y1;
  y2_ = y2;
}


double Box::width() const {
  return x2_ - x1_;
}

double Box::height() const {
  return y2_ - y1_;
}

bool Box::isForward() const {
  return width() >= 0.0;
}

