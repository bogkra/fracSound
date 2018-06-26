#pragma once

#include <vector>
#include <algorithm>
#include "Box.hpp"
#include "Wave.hpp"

using Parts = std::vector<Box>;

class Fractal {
public: 
  Fractal(Wave & wave,  Box & box, const std::vector<Box> parts) : wave_(wave), box_(box), parts_(parts) {};
  void run(const Box & box, const int level);

private:
  Wave & wave_;
  Box & box_;
  Parts parts_;
};


