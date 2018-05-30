#include "WaveFile.hpp"

int main() {
  Wave* pWave  = new(Wave);
  Wave & wave = *pWave;
  Range xs1(0.0, 100.0);
  Range ys(0.0, 123.456);
  Box box1(xs1, ys);
  wave.sine(box1);

  Range xs2(100, 200);
  Box box2(xs2, ys);
  wave.sine(box2);

  wave.normalize();

  delete(pWave);   
}


