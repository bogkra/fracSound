#pragma once
#include "Range.hpp"

class Box {
public:
  Box(const Range xRange, const Range yRange) : xRange_(xRange), yRange_(yRange) {};
  Range getXRange() const {return xRange_;};
  Range getYRange() const {return yRange_;};
  double width() const;
  double height() const;
  bool isForward() const;
private:
  Range xRange_;
  Range yRange_;
};


