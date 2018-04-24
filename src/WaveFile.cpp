#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>    
#include <time.h>      
#include <array>      
#include "Wave.hpp"

using namespace std;
using namespace LittleEndianIo;
using namespace Config;

Wave::Wave() {
  samples.fill(0.0);
}

bool Wave::write(const int where, const double& what) {
  if (where<MAX_SIZE) {
    samples.at(where) += what;
    sampleIndex = max(sampleIndex, where);
    return true;
  } 
  return false;
}

void Wave::normalize() {
  double maxAmplitude = 0;
  for (const auto amplitude: samples) 
    maxAmplitude = max(maxAmplitude, abs(amplitude));
  if (maxAmplitude>verySmall)
    for (auto& amplitude: samples) 	
      amplitude /= maxAmplitude;
}

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


void Wave::simpleSine(const double maxAmplitude) {
  const double c4Frequency = 261.626;  
  const double frequency = c4Frequency;
  const double seconds   = 2.5; 
  int numberOfSamples = seconds * samplesPerSecond;  
  for (int i = 0; i < numberOfSamples; i++) {
    double value = sin( twoPi * i * frequency / samplesPerSecond );
    write(i, maxAmplitude * value);
  }
}

void Wave::sine(const int x1, const int x2, const double amplitude) {
  for (int i = x1; i < x2; i++) {
    const int length = x2 - x1;
    double standardValue     = sin( twoPi *(i-x1)/length );
    write(i, 1.0 * amplitude * standardValue);
  }  
}

void Wave::writeToSamples() {
  int x = 0;
  for (int i = 0; i<3000; i++) {
    int amplitude = rand() * 0.0001;
    int length = rand() % 500;
    sine(x, x + length, amplitude);
    x += length;
  }  
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



