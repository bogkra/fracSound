#include "Box.hpp"


double Box::width() const {
  return xRange_.length();
}

double Box::height() const {
  return yRange_.length();
}

bool Box::isForward() const {
  return xRange_.isForward();
}

void Box::rescale(Box outside) {
  xRange_.rescale(outside.getXRange());
  yRange_.rescale(outside.getYRange());
  
}

void Box::equallyRescale(const double alpha) {
  xRange_.rescale(alpha);
  yRange_.rescale(alpha);
}


void Box::widthRescale(const double alpha) {
  xRange_.rescale(alpha);
}

void Box::widthyRescale(const double alpha) {
  equallyRescale(alpha);
  yRange_.moveDown();
}

