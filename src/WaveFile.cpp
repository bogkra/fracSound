#include "WaveFile.hpp"
#include "Incrementator.hpp"
#include "FileHeader.hpp"

using namespace std;
using namespace LittleEndianIo;

WaveFile::WaveFile(const std::string& fileName, Wave* pWave) {    
  file.open(fileName, ios::binary);
  FileHeader fileHeader(this);  
  size_t dataChunkPos = file.tellp();
  writeDataChunkHeader(); 

  samplesToFile(*pWave);

  size_t positionAfterData = file.tellp();
  fixDataChunkHeader(dataChunkPos, positionAfterData);
  fixFileHeader(positionAfterData);
}

void WaveFile::samplesToFile(Wave& wave) {
  const double maxAmplitude = 32767;  
  wave.normalize();  
  for (auto normalizedAmplitude: wave.getSamples()) {
      writeWord(file, (int)(normalizedAmplitude.left * maxAmplitude), 2);         
      writeWord(file, (int)(normalizedAmplitude.right * maxAmplitude), 2);         
  }
}

void WaveFile::writeToFile(const int value, const unsigned size) {
  writeWord(file, value, size);
}

void WaveFile::writeDataChunkHeader() {
  file << "data----";  
}

void WaveFile::fixDataChunkHeader(const size_t dataChunkPos, const size_t positionAfterData) {
  file.seekp(dataChunkPos + 4 );
  size_t size = positionAfterData - dataChunkPos;
  writeWord(file, size + 8 );
}

void WaveFile::fixFileHeader(const size_t positionAfterData) {
  file.seekp( 0 + 4 );
  writeToFile(positionAfterData - 8, 4 ); 
  file.close();
}	





