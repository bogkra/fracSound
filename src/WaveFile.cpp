#include "WaveFile.hpp"

using namespace std;
using namespace LittleEndianIo;
using namespace Config;


void WaveFile::samplesToFile(Wave& wave) {
  const double maxAmplitude = 32767;  
  wave.normalize();  
  for (const auto normalizedAmplitude: wave.samples)
    for (auto position : positions) {
       writeWord(file, (int)(normalizedAmplitude*maxAmplitude), 2);
       (void)position;
    }
}


void WaveFile::writeToFile(const int value, const unsigned size) {
  writeWord(file, value, size);
}

void WaveFile::writeBytesPerSecond() {
  writeToFile(samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
}

void WaveFile::writeDataBlockSize() {
  writeToFile(bytesPerSample * numberOfChannels, 2 );  
}
	
void WaveFile::writeHeader() {
  file << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  writeToFile(16, 4 );  // no extension data
  writeToFile(1, 2 );  // PCM - integer samples
  writeToFile(numberOfChannels, 2 );  
  writeToFile(samplesPerSecond, 4 );  
  writeBytesPerSecond(); 
  writeDataBlockSize(); 
  writeToFile(bitsPerSample, 2 );  
}


void WaveFile::writeSamples(Wave& wave) {
  wave.writeToSamples();
  samplesToFile(wave);
}

WaveFile::WaveFile(const std::string& fileName, Wave* pWave){    
  file.open(fileName, ios::binary);
  srand(time(NULL));
  writeHeader();

  // Write the data chunk header
  size_t dataChunkPos = file.tellp();
  getFile() << "data----";  // (chunk size to be filled in later)
  
  writeSamples(*pWave);

  size_t positionAfterData = file.tellp();

  // Fix the data chunk header to contain the data size
  getFile().seekp(dataChunkPos + 4 );
  writeWord(file, positionAfterData - dataChunkPos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  getFile().seekp( 0 + 4 );
  writeToFile(positionAfterData - 8, 4 ); 
}



