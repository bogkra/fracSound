#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <utility>
#include "Box.hpp"


namespace Channels {
  const int mono = 1;
  const int stereo = 2;
  const int surround = 5 + 1 ;
}

enum Position {
  leftPos,
  rightPos
};


namespace Config {
  const int numberOfChannels = Channels::stereo ;  
  const int bytesPerSample = 2;
  const int bitsPerSample = 8 * bytesPerSample;
  const int samplesPerSecond = 44100;
  constexpr double pi = acos(-1);
  const int MAX_NO_SAMPLES = 2 * samplesPerSecond;
  const std::vector<Position> positions = {Position::leftPos, Position::rightPos};
}

//using Samples = std::array<double, Config::MAX_NO_SAMPLES> ;
//class Stereo {
//}

using Stereo  = std::pair<double, double>;
using Samples = std::array<Stereo, Config::MAX_NO_SAMPLES> ;


class Wave {
public: 
  Wave();
  ~Wave();
//  void writeToSamples();
  void sine(const Box& box);
  void line(const Box& box, const Stereo panorama = Stereo(1,1)) ;
  void simpleSine(const double maxAmplitude);
  void normalize();

  Samples& getSamples()  {return samples_;};  

private:
//  void writeToSample(int & moment);
  bool write(const int where, const double& what, const Stereo panorama);
  void normalize(const double maxAmplitude);
  double maxAmplitude();

  Samples * pSamples {new Samples};
  Samples & samples_ = *pSamples;  
//  Samples samples_;  

};

bool absCompare(Stereo a, Stereo b);
bool isVerySmall(const double number);

