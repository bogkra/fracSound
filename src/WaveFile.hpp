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
  WaveFile(const std::string& fileName, Wave* pWave);    
 
private:
  std::ofstream file;

  void writeToFile(const int value, const unsigned size);
  void writeBytesPerSecond();
  void writeDataBlockSize();
  void samplesToFile(Wave& wave);
  void writeHeader();
  void writeEmptyChunkSize();
  void writeNoExtensionData();
  void writePsmIntegerSamples();
  void writeDataChunkHeader();
  void fixDataChunkHeader(const size_t dataChunkPos, const size_t positionAfterData);
  void fixFileHeader(const size_t positionAfterData);
};

void doIt();
