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
  Fractal(Wave & wave,  Box & box, const Parts parts);
  Fractal(Wave & wave,  Box & box, const Points points);
  void run(const Box & box, const int level);

private:
  Wave & wave_;
  Box & box_;
  Parts parts_;
  Points points_;

  void pointToPart(Points::iterator it);
};


