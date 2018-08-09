#include "Box.hpp"


double Box::width() const {
  return xRange_.length();
}

double Box::height() const {
  return yRange_.length();
}

void Box::widthRescale(const double & alpha) {
  xRange_.rescale(alpha);
}

void Box::heightRescale(const double & alpha) {
  yRange_.rescale(alpha);
}

void Box::widthyRescale(const Box & outside, const double & alpha) {
  xRange_.rescale(outside.getXRange());
  yRange_.rescale(alpha); 
}

void Box::move(const double & x) {
  xRange_.move(x);
}
