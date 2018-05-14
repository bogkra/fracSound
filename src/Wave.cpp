#include <cmath>
#include "Wave.hpp"
#include "Incrementator.hpp"

using namespace std;
using namespace Config;

Wave::Wave() {
  srand(time(NULL));
  samples_.fill(0.0);
}

void Wave::writeToSamples() {
  int x = 0;
  for (Incrementator i; i.times(30000);) {
    int amplitude = (rand() % 1000000) * 0.0001;
    int length = rand() % 500;
    Range xs(x, x+length);
    Range ys(0.0, amplitude);
    Box box(xs, ys);
    sine(box);
    x += length;
  }  
}

void Wave::sine(const Box& box) {
  for (int i = 0; i < box.width(); i++) {
    double standardValue = sin( 2.0 * pi * i / box.width() );
    write(box.getXRange().getBegin() + i, box.getYRange().getBegin() + box.height() * standardValue);
  }  
}

void Wave::line(const Box& box) {
  for (int i = box.getXRange().getBegin();  
       i !=  (int)box.getXRange().getEnd();
       box.isForward() ? i++ : i--) {
         int tempWidth = i - box.getXRange().getBegin();
         write(i, box.getYRange().getBegin() + box.height() * tempWidth / box.width());
  }
}

void Wave::simpleSine(const double maxAmplitude) {
  const double c4Frequency = 261.626;  
  const double seconds   = 2.5; 
  int numberOfSamples = seconds * samplesPerSecond;  
  for (int i = 0; i < numberOfSamples; i++) {
    double value = sin( 2.0 * pi * i * c4Frequency / samplesPerSecond );
    write(i, maxAmplitude * value);
  }
}

bool Wave::write(const int where, const double& what) {
  if (where < MAX_NO_SAMPLES and where >= 0) {
    samples_.at(where) += what;
    return true;
  } 
  return false;
}

void Wave::normalize() {
  double maxAmplitude = 0;
  for (const auto amplitude: samples_) 
    maxAmplitude = max(maxAmplitude, abs(amplitude));
  if (maxAmplitude>verySmall)
    for (auto& amplitude: samples_) {	
      amplitude /= maxAmplitude;
    }
}
