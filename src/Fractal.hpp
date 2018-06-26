#pragma once

#include <array>
#include <algorithm>
#include "Box.hpp"
#include "Wave.hpp"

 
using Parts = std::array<Box, 0>;


class Fractal {
public: 
  Fractal(Wave & wave,  Box & box, const Parts & parts) : wave_(wave), box_(box), parts_(parts) {};
  void run(const Box & box, const int level);

private:
  Wave & wave_;
  Box & box_;
  Parts parts_;
};


