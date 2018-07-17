#include <cmath>
#include <iostream>
#include <algorithm>
#include "Fractal.hpp"


using namespace std;

Fractal::Fractal(Wave & wave, const Parts parts) : wave_(wave), parts_(parts) {
}


Fractal::Fractal(Wave & wave,  const Points points) : wave_(wave), points_(points) {
  points_.insert(points_.begin(), Point(0,0)); 
  points_.push_back(Point(1, 0)); 
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
  Box drawBox = outsideBox;
  drawBox.widthRescale(positions_.length());   
  drawBox.move(positions_.getBegin()); 
  wave_.line(drawBox);
  if (level > 0) 
    for (Box part : parts_) {    
      Box newBox = part;
      double alpha = outsideBox.width()/1.0;
      newBox.widthyRescale(outsideBox, alpha);
      run(newBox, level - 1);
    }
}

void Fractal::start(const int level) {
  Box box(Range(0,1), Range(0,0)); 
  run(box, level);
}



