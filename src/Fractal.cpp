#include <cmath>
#include "Fractal.hpp"


using namespace std;


void Fractal::run(const Box & box, const int level) {
  if (level==0)
    wave_.line(box);
  else 
    for (auto part : parts_) {
      Box newBox = part;
      newBox.rescale(box); 
      run(newBox, level - 1);
    }
}


