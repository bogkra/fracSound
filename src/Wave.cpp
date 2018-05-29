#include <cmath>
#include "Wave.hpp"
#include "Incrementator.hpp"
#include "Accumulator.hpp"

using namespace std;
using namespace Config;

Wave::Wave() {
  srand(time(NULL));
  samples_.fill(0.0);
}

bool Wave::write(const int where, const double& what) {
  if (where < MAX_NO_SAMPLES and where >= 0) {
    samples_.at(where) += what;
    return true;
  } 
  return false;
}

void Wave::writeToSamples() {
  int x = 0;
  30000 * [&] {
    int amplitude = (rand() % 1000000) * 0.0001;
    int length = rand() % 500;
    Range xs(x, x+length);
    Range ys(0.0, amplitude);
    Box box(xs, ys);
    sine(box);
    x += length;
  }; 
}

void Wave::sine(const Box& box) {
  box.width() * [&] (int i)  {
    double standardValue = sin( 2.0 * pi * i / box.width() );
    write(box.getXRange().getBegin() + i, box.getYRange().getBegin() + box.height() * standardValue);
  };
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
  const double c4Frequency = 261.626,  
                   seconds = 2.5; 
  int numberOfSamples = seconds * samplesPerSecond;  
  numberOfSamples * [&](int i) {
    double value = sin( 2.0 * pi * i * c4Frequency / samplesPerSecond );
    write(i, maxAmplitude * value);
  };
}

void Wave::normalize() {
  double maxAmpl = maxAmplitude();
  if (maxAmpl > verySmall)
    normalize(maxAmpl);
}

double Wave::maxAmplitude() {
  double result = 0;
  for (const double amplitude : samples_) 
    result = max(result, abs(amplitude));
  return result;
}

void Wave::normalize(const double maxAmplitude) {
  for (auto& amplitude : samples_) 
    amplitude /= maxAmplitude;
}
