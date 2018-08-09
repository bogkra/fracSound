#include <cmath>
#include <iostream>
#include <algorithm>
#include "Fractal.hpp"

using namespace std;

Fractal::Fractal(Wave & wave,  const Points & points) : wave_(wave), points_(points) {
  lineFunction_  = &Wave::line;
  setPoints(points);
}

void Fractal::setPoints(const Points & points) {
  points_ = points;
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
  line(outsideBox);
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

void Fractal::line(const Box & outsideBox) { 
  Box drawBox = outsideBox;
  drawBox.widthRescale(positions_.length());   
  drawBox.heightRescale(power_);   
  drawBox.move(positions_.getBegin()); 
  (wave_.*lineFunction_)(drawBox, panorama_);
}

void Fractal::setPanorama(const Stereo & panorama) {
  panorama_.left = panorama.left;
  Range range01(0.0, 1.0);
  range01.intoBoundaries(panorama_.left);
  panorama_.right = panorama.right;
  range01.intoBoundaries(panorama_.right);
}
