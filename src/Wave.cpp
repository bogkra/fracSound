#include <cmath>
#include <iostream>
#include "algorithm"
#include "Wave.hpp"
#include "Incrementator.hpp"

using namespace std;
using namespace Config;

Wave::Wave() {
  srand(time(NULL));
//  srand(9);
  samples_.fill(Stereo(0.0, 0.0));
}

Wave::~Wave() {
  delete pSamples;
}

bool Wave::write(const int where, const double& what, const Stereo & panorama = Stereo(1,1)) {
  if (Range(0, MAX_NO_SAMPLES-1).isBetween(where)) {
    samples_.at(where).left += what * panorama.left;
    samples_.at(where).right += what * panorama.right;
    return true;
  } 
  return false;
}

void Wave::sine(const Box & box, const Stereo & panorama) {
  box.width() * [&] (int i)  {
    double standardValue = sin( 2.0 * pi * i / box.width() );
    write(box.getXRange().getBegin() + i, box.getYRange().getBegin() + box.height() * standardValue, panorama);
  };
}

void Wave::halfSine(const Box & box, const Stereo & panorama) {
  box.width() * [&] (int i)  {
    double standardValue = 1.0 + sin( 1.0 * pi *  (i / box.width() - 0.5 ) );
    write(box.getXRange().getBegin() + i, box.getYRange().getBegin() + box.height() * standardValue, panorama);
  };
}

void Wave::line(const Box & box, const Stereo & panorama) {
  const int begin = box.getXRange().min();
  const int   end = box.getXRange().max();    
//TODO: opposite direction !?

  double alpha = 1;
  if (begin==end) 
    alpha = box.getXRange().max() - box.getXRange().min();
  for (int tempWidth = 1 ; tempWidth<= end - begin; tempWidth++ ) 
     write(begin + tempWidth, alpha * (box.getYRange().getBegin() + box.height() * tempWidth / (end - begin)), panorama);
}

void Wave::simpleSine(const double & maxAmplitude) {
  const double c4Frequency = 261.626,  
                   rights = 2.5; 
  int numberOfSamples = rights * samplesPerSecond;  
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
  return max(result.left, result.right);
}

bool absCompare(const Stereo & a, const Stereo & b) {
  return max(abs(a.left), abs(a.right)) < max(abs(b.left), abs(b.right));
}

void Wave::normalize(const double & maxAmplitude) {
  for (auto& amplitude : samples_) {
    amplitude.left /= maxAmplitude;
    amplitude.right /= maxAmplitude;
  }
}

bool isVerySmall(const double & number) {
  const double verySmall = 1E-15;
  return abs(number) <= verySmall;
}

