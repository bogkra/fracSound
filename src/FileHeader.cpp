#include "WaveFile.hpp"
#include "Incrementator.hpp"

using namespace std;
using namespace LittleEndianIo;
using namespace Config;

WaveFile::WaveFile(const std::string& fileName, Wave* pWave) {    
  file.open(fileName, ios::binary);
  writeHeader();
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

void WaveFile::writeHeader() {
  writeEmptyChunkSize();
  writeNoExtensionData();
  writePsmIntegerSamples();
  writeToFile(numberOfChannels, 2 );  
  writeToFile(samplesPerSecond, 4 );  
  writeBytesPerSecond(); 
  writeDataBlockSize(); 
  writeToFile(bitsPerSample, 2 );  
}

void WaveFile::writeEmptyChunkSize() {
  file << "RIFF----WAVEfmt "; 
}

void WaveFile::writeNoExtensionData() {
  writeToFile(16, 4 );  
}

void WaveFile::writePsmIntegerSamples() {
  writeToFile(1, 2 );  
}

void WaveFile::writeToFile(const int value, const unsigned size) {
  writeWord(file, value, size);
}

void WaveFile::writeBytesPerSecond() {
  writeToFile(samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
}

void WaveFile::writeDataBlockSize() {
  writeToFile(bytesPerSample * numberOfChannels, 2 ) ;  
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





