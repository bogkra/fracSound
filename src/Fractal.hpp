#pragma once

#include <vector>
#include <utility>
#include "Box.hpp"
#include "Wave.hpp"

using Parts = std::vector<Box>;
using Point = std::pair<double, double>;
using Points = std::vector<Point>;
using LineFunction = void (Wave::*) (const Box & outsideBox, const Stereo & panorama);

class Fractal {
public: 
  Fractal(Wave & wave) : wave_(wave) {lineFunction_  = &Wave::line;};
  Fractal(Wave & wave, const Parts & parts) : wave_(wave), parts_(parts) {lineFunction_  = &Wave::line;};
  Fractal(Wave & wave, const Points & points);
  void setPositions(const Range & positions) {positions_ = positions;};
  void setPoints(const Points & points);
  void setPower(const double & power) {power_ = power;};
  void start(const int level);
  void setPanorama(const Stereo & panorama);
  void setLineFunction(LineFunction lineFunction) {lineFunction_ = lineFunction;};

private:
  LineFunction lineFunction_;
  Wave & wave_;
  Range positions_ = {0, 100};
  double power_ = 1.0;
  Stereo panorama_ = Stereo(1, 1);  

  Parts parts_;
  Points points_;

  void run(const Box & box, const int level);
  void line(const Box & outsideBox);
  void pointToPart(const Points::iterator & it);
};
