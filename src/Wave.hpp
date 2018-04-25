#pragma once

#include <array>
#include <vector>

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
  const double twoPi = 6.283185307179586476925286766559;
  const int MAX_SIZE = 20 * samplesPerSecond;
  const double verySmall = 1E-15;
  const std::vector<Position> positions = {Position::leftPos, Position::rightPos};
}


class Wave {
public: 
  Wave();
  void normalize();
  void writeToSamples();
  void simpleSine(const double maxAmplitude);
  void sine(const int x1, const int x2, const double amplitude);

  std::array<double, Config::MAX_SIZE> samples;  
private:
  bool write(const int where, const double& what);
  int sampleIndex = 0;  
};



