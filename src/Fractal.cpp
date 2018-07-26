#include <cmath>
#include <iostream>
#include <algorithm>
#include "Fractal.hpp"


using namespace std;

Fractal::Fractal(Wave & wave, const Parts & parts) : wave_(wave), parts_(parts) {
}


Fractal::Fractal(Wave & wave,  const Points & points) : wave_(wave), points_(points) {
  points_.insert(points_.begin(), Point(0,0)); 
  points_.push_back(Point(1, 0)); 
  for (auto it = points_.begin();  next(it) != points_.end(); it++) 
    pointToPart(it);
}

void Fractal::pointToPart(const Points::iterator & it) {
  Range times(it->first, next(it)->first); 
  Range amplitudes(it->second, next(it)->second); 
  Box tempBox(times, amplitudes);
  parts_.push_back(tempBox); 
}

void Fractal::start(const int level) {
  const Box box(Range(0,1), Range(0,0)); 
  run(box, level);
}

void Fractal::run(const Box & outsideBox, const int level) {
  Box drawBox = outsideBox;
  drawBox.widthRescale(positions_.length());   
  drawBox.heightRescale(power_);   
  drawBox.move(positions_.getBegin()); 
  wave_.line(drawBox, panorama_);


  if (level > 0) {
    Box newBox(Range(0,0), Range(0,0));
    double alpha;
    for (Box & part : parts_) {    
      newBox = part;
      alpha = outsideBox.width()/1.0;
      newBox.widthyRescale(outsideBox, alpha);
      run(newBox, level - 1);
    }
  }
}


void Fractal::setPanorama(const Stereo & panorama) {
//  double value = panorama.first;
//  if (Range(0,1).isBetween(value))

  panorama_.first = panorama.first;
//  else if (value<0) panorama_.first = 0;
//  else if (value>1) panorama_.first = 1;

//  double value2 = panorama.second;
//  if (Range(0,1).isBetween(value2))
  panorama_.second = panorama.second;

}



