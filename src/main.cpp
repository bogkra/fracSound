#include "WaveFile.hpp"

void doIt() {
  Wave* pWave = new(Wave);
//  Wave wave;

  WaveFile waveFile("example.wav");
  // Write the data chunk header
  size_t dataChunkPos = waveFile.file.tellp();
  waveFile.file << "data----";  // (chunk size to be filled in later)
  
  waveFile.writeSamples(*pWave);

  size_t positionAfterData = waveFile.file.tellp();

  // Fix the data chunk header to contain the data size
  waveFile.file.seekp( dataChunkPos + 4 );
  LittleEndianIo::writeWord( waveFile.file, positionAfterData - dataChunkPos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  waveFile.file.seekp( 0 + 4 );
  LittleEndianIo::writeWord( waveFile.file, positionAfterData - 8, 4 ); 

  delete(pWave);
}

int main() {
  doIt();
}


