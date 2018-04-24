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
	
void WaveFile::writeHeader() {
  file << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  writeWord( file,     16, 4 );  // no extension data
  writeWord( file,      1, 2 );  // PCM - integer samples
  writeWord( file, numberOfChannels, 2 );  
  writeWord( file, samplesPerSecond, 4 );  
  writeWord( file, samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
  writeWord( file, numberOfChannels * bytesPerSample, 2 );  // data block size 
  writeWord( file, bitsPerSample, 2 );  
}


void WaveFile::writeSamples(Wave& wave) {
  wave.writeToSamples();
  samplesToFile(wave);
}

WaveFile::WaveFile(const std::string& fileName){    
  file.open(fileName, ios::binary);
  srand(time(NULL));
  writeHeader();
}



