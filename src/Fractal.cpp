#include <cmath>
#include "Fractal.hpp"


using namespace std;


void Fractal::run(const Box & box, const int level) {
  if (level==0)
    wave_.line(box);
  else {
    Range times(0, parts_.at(0).getXRange().getBegin()); 
    Range amplitudes(0, parts_.at(0).getYRange().getBegin()); 
    Box newBox(times, amplitudes);
    newBox.rescale(box); 
    run(newBox, level - 1);
    for (auto part : parts_) {
      Box newBox = part;
      newBox.rescale(box); 
      run(newBox, level - 1);
    }
//    Box newBox(parts_.back()
    
  }
}


