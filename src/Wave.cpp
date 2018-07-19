#include <cmath>
#include <iostream>
#include "algorithm"
#include "Wave.hpp"
#include "Incrementator.hpp"
#include "Accumulator.hpp"

using namespace std;
using namespace Config;


Wave::Wave() {
  srand(time(NULL));
  samples_.fill(Stereo(0.0, 0.0));
}

Wave::~Wave() {
  delete pSamples;
}

bool Wave::write(const int where, const double& what, const Stereo panorama = Stereo(1,1)) {
  if (where < MAX_NO_SAMPLES and where >= 0) {
    samples_.at(where).first += what * panorama.first;
    samples_.at(where).second += what * panorama.second;
//    cout << where << ":" << what << " ";
    return true;
  } 
  return false;
}

/*
void Wave::writeToSample(int & moment) {
  int amplitude = (rand() % 1000000) * 0.0001;
  int period = rand() % 500;
  Range times(moment, moment + period);
  Range amplitudes(0.0, amplitude);
  Box box(times, amplitudes);
  sine(box);
  moment += period;
}

void Wave::writeToSamples() { 
  int moment = 0;
  const int exemplaryComplexity = 30000;
  exemplaryComplexity * [&] {
    writeToSample(moment);
  };
}
*/

void Wave::sine(const Box& box) {
  box.width() * [&] (int i)  {
    double standardValue = sin( 2.0 * pi * i / box.width() );
    write(box.getXRange().getBegin() + i, box.getYRange().getBegin() + box.height() * standardValue);
  };
}

void Wave::line(const Box& box, const Stereo panorama) {
  const int begin = box.getXRange().min();
  const int   end = box.getXRange().max();    
//TODO: opposite direction !?


  for (Incrementator tempWidth; tempWidth.repeat(end - begin);) {
     write(begin + tempWidth, box.getYRange().getBegin() + box.height() * tempWidth / (end - begin), panorama);
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
  if (not isVerySmall(maxAmpl))
    normalize(maxAmpl);
}

double Wave::maxAmplitude() {
  Stereo result = *max_element(samples_.begin(), samples_.end(), absCompare);
  return max(result.first, result.second);
}

bool absCompare(Stereo a, Stereo b) {
  return max(abs(a.first), abs(a.second)) < max(abs(b.first), abs(b.second));
}

void Wave::normalize(const double maxAmplitude) {
  for (auto& amplitude : samples_) {
    amplitude.first /= maxAmplitude;
    amplitude.second /= maxAmplitude;
  }
}

bool isVerySmall(const double number) {
  const double verySmall = 1E-15;
  return abs(number) <= verySmall;
}

