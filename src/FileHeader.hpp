#pragma once

#include "WaveFile.hpp"

class FileHeader {
public:
  FileHeader(WaveFile* pFile);
 
private:
  WaveFile * pFile_;

  void writeEmptyChunkSize();
  void writeNoExtensionData();
  void writePsmIntegerSamples();
  void writeBytesPerSecond();
  void writeDataBlockSize();
};

