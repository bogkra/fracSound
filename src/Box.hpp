#pragma once
#include "Range.hpp"

class Box {
public:
  Box(const Range xRange, const Range yRange) : xRange_(xRange), yRange_(yRange) {};
  Range getXRange() const {return xRange_;};
  Range getYRange() const {return yRange_;};
  void setXRange(const Range r) { xRange_ = r;};
  void setYRange(const Range r) { yRange_ = r;};
  double width() const;
  double height() const;
  bool isForward() const;
  void rescale(Box outside);
  void equallyRescale(const double alpha);
  void widthRescale(const double alpha);
  void widthyRescale(const Box & outside, const double alpha);
private:
  Range xRange_;
  Range yRange_;
};


