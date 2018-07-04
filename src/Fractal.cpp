#include <cmath>
#include <iostream>
#include <algorithm>
#include "Fractal.hpp"


using namespace std;

Fractal::Fractal(Wave & wave,  Box & box, const Parts parts) : wave_(wave), box_(box), parts_(parts) {
}


Fractal::Fractal(Wave & wave,  Box & box, const Points points) : wave_(wave), box_(box), points_(points) {
  points_.insert(points_.begin(), Point(0,0)); 
  points_.push_back(Point(1.0, 0.0)); 
  for (auto it = points_.begin();  next(it) != points_.end(); it++) 
    pointToPart(it);
}

void Fractal::pointToPart(Points::iterator it) {
  Range times(it->first, next(it)->first); 
  Range amplitudes(it->second, next(it)->second); 
  Box tempBox(times, amplitudes);
  parts_.push_back(tempBox); 
}


void Fractal::run(const Box & outsideBox, const int level) {
  if (level == 0) 
    wave_.line(outsideBox);
  else 
    for (auto part : parts_) {    
      Box newBox = part;
      newBox.rescale(outsideBox); 
      run(newBox, level - 1);
    }
}

//skandynawska w rynku (w paryzu??)

//12-13
// 09881
