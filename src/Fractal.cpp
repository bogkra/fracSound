#include <cmath>
#include <iostream>
#include "Fractal.hpp"


using namespace std;

Fractal::Fractal(Wave & wave,  Box & box, const Parts parts) : wave_(wave), box_(box), parts_(parts) {
//  Range times(0, parts.front().getXRange().getBegin()); 
//  Range amplitudes(0, parts_.front().getYRange().getBegin()); 
//  Box newBox(times, amplitudes);
//  parts_.insert(parts_.begin(),newBox);
}



void Fractal::run(const Box & box, const int level) {
  if (level == 0)
    wave_.line(box);
  else {
//TODO DRY broken!
    Range times(0, parts_.front().getXRange().getBegin()); 
    Range amplitudes(0, parts_.front().getYRange().getBegin()); 
    Box newBox(times, amplitudes);
    newBox.rescale(box); 
    run(newBox, level - 1); 
    for (auto part : parts_) {    
      Box newBox = part;
      newBox.rescale(box); 
      run(newBox, level - 1);
    }
    Range times2(parts_.back().getXRange().getEnd(), 1.0); 
    Range amplitudes2(parts_.back().getYRange().getEnd(), 1.0); 
    Box newBox2(times2, amplitudes2);
    newBox2.rescale(box); 
    run(newBox2, level - 1); 
  }
}


