#pragma once

#include <fstream>
#include "Wave.hpp"


namespace LittleEndianIo {
  template <typename Word>
  std::ostream& writeWord( std::ostream& outs, Word value, unsigned size = sizeof( Word ) ) {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}

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
