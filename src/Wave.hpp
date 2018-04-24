#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>    
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

namespace LittleEndianIo {
  template <typename Word>
  std::ostream& writeWord( std::ostream& outs, Word value, unsigned size = sizeof( Word ) ) {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}

namespace Config {
  const int numberOfChannels = Channels::stereo ;  
  const int bytesPerSample = 2;
  const int bitsPerSample = 8*bytesPerSample;
  const int samplesPerSecond = 44100;
  const double twoPi = 6.283185307179586476925286766559;
  const int MAX_SIZE = 5*samplesPerSecond;
  const double verySmall = 1E-15;
  const std::vector<Position> positions = {Position::leftPos, Position::rightPos};
}


class Wave {
public: 
  Wave();
  bool write(const int where, const double& what);
  void writeToSamples();
  void normalize();
  void simpleSine(const double maxAmplitude);
  void sine(const int x1, const int x2, const double amplitude);
  std::array<double, Config::MAX_SIZE> samples;  
private:
  int sampleIndex = 0;  
};

class WaveFile {
public:
  WaveFile(const std::string& fileName);    
  void writeHeader();
  void samplesToFile(Wave& wave);
  void writeSamples(Wave& wave);
  std::ofstream file;
private:
};

void doIt();
