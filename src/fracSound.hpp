#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>    
#include <array>

namespace Channels {
  const int mono = 1;
  const int stereo = 2;
  const int surround = 5 + 1 ;
}

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
  const int MAX_SIZE = 0.1*samplesPerSecond;
  const double verySmall = 0.0000000000001;

}



class Wave {
public: 
  bool write(int where, double what);
  void normalize();
  void samplesToFile(std::ofstream& file);
  void simpleSine(const double maxAmplitude);
  void sine(const int length, const double amplitude);
  void writeSamples(std::ofstream& file);
  void init(std::ofstream& file);
  void writeToSamples();

  std::array<double, Config::MAX_SIZE> samples;

private:
  int sampleIndex = 0;  
};

using namespace LittleEndianIo;






void simpleSine(const double maxAmplitude);
void sine(const int length, const double amplitude);
void writeToWave();


void doIt();
