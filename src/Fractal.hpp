#pragma once

#include <vector>
#include <algorithm>
#include <utility>
#include "Box.hpp"
#include "Wave.hpp"

using Parts = std::vector<Box>;
using Point = std::pair<double, double>;

class Fractal {
public: 
  Fractal(Wave & wave,  Box & box, const Parts parts);
  void run(const Box & box, const int level);

private:
  Wave & wave_;
  Box & box_;
  Parts parts_;
};


