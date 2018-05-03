#pragma once

#include <vector>
#include "Box.hpp"

 
using Parts = std::vector<Box>;

class Fractal {
public: 
Fractal(const Box box, const Parts parts) : box_(box), parts_(parts) {};

private:
  Box box_;
  Parts parts_;
};


