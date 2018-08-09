#include "WaveFile.hpp"


#include <iostream>
#include <string>
#include <vector>


int main() {
  Wave wave;
  Range xs1(0.0, 100.0);
  Range ys(0.0, 123.456);
  Box box1(xs1, ys);
  wave.sine(box1, Stereo(1,1));

  Range xs2(100, 200);
  Box box2(xs2, ys);
  wave.sine(box2, Stereo(1,1));

  wave.normalize();


  return 0;
}



