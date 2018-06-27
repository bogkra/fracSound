#include <cmath>
#include <iostream>
#include "Fractal.hpp"


using namespace std;

Fractal::Fractal(Wave & wave,  Box & box, const Parts parts) : wave_(wave), box_(box), parts_(parts) {
  if (not parts_.empty()) {
    Range times(0, parts_.front().getXRange().getBegin()); 
    Range amplitudes(0, parts_.front().getYRange().getBegin()); 
    Box newBox(times, amplitudes);
    parts_.insert(parts_.begin(),newBox);

    //TODO DRY broken?
    Range times2(parts_.back().getXRange().getEnd(), 1.0); 
    Range amplitudes2(parts_.back().getYRange().getEnd(), 1.0); 
    Box newBox2(times2, amplitudes2);
    parts_.push_back(newBox2);
  }
}


void Fractal::run(const Box & box, const int level) {
  if (level == 0)
    wave_.line(box);
  else 
    for (auto part : parts_) {    
      Box newBox = part;
      newBox.rescale(box); 
      run(newBox, level - 1);
    }
}
