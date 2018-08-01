#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <utility>
#include "Box.hpp"
#include "Stereo.hpp"
#include "Config.hpp"

using Samples = std::array<Stereo, Config::MAX_NO_SAMPLES> ;

class Wave {
public: 
  Wave();
  ~Wave();
  void sine(const Box& box);
  void line(const Box& box, const Stereo & panorama = Stereo(1,1)) ;
  void simpleSine(const double & maxAmplitude);
  void normalize();

  const Samples& getSamples()  {return samples_;};  

private:
  bool write(const int where, const double & what, const Stereo & panorama);
  void normalize(const double & maxAmplitude);
  double maxAmplitude();

  Samples * pSamples {new Samples};
  Samples & samples_ = *pSamples;  
};

bool absCompare(const Stereo & a, const Stereo & b);
bool isVerySmall(const double & number);

