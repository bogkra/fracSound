#pragma once

#include <array>
#include <algorithm>
#include "Box.hpp"
#include "Wave.hpp"

 
using Parts = std::array<Box, 12>;


class Fractal {
public: 
  Fractal(const Box box, const Parts parts) : box_(box), parts_(parts) {};
//  Fractal(const Box box, const Parts parts, const Wave & wave) : box_(box), parts_(parts), wave_(wave) {};
  void run(const Box & box, const int level);

private:
  Box box_;
  Parts parts_;
//  Wave & wave_;
};


