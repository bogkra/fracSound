#pragma once

#include <vector>
#include <utility>
#include "Box.hpp"
#include "Wave.hpp"

using Parts = std::vector<Box>;
using Point = std::pair<double, double>;
using Points = std::vector<Point>;

class Fractal {
public: 
  Fractal(Wave & wave, const Parts parts);
  Fractal(Wave & wave, const Points points);
  void start(const int level);

private:
  Wave & wave_;
  Parts parts_;
  Points points_;

  void run(const Box & box, const int level);
  void pointToPart(Points::iterator it);
};


