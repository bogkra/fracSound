#include "Box.hpp"


double Box::width() const {
  return xRange_.length();
}

double Box::height() const {
  return yRange_.length();
}

bool Box::isForward() const {
  return width() >= 0.0;
}

void Box::rescale(Box outside) {
  xRange_.rescale(outside.getXRange());
  yRange_.rescale(outside.getYRange());
  
}
