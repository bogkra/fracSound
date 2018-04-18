#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>    
#include <time.h>      
#include "fracSound.hpp"

using namespace std;

namespace LittleEndianIo {
  template <typename Word>
  std::ostream& writeWord( std::ostream& outs, Word value, unsigned size = sizeof( Word ) ) {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}

using namespace LittleEndianIo;


namespace Channels {
  const int mono = 1;
  const int stereo = 2;
  const int surround = 5 + 1 ;
}

namespace Config {
  const int numberOfChannels = Channels::stereo ;  
  const int bytesPerSample = 2;
  const int bitsPerSample = 8*bytesPerSample;
  const int samplesPerSecond = 44100;
  const double twoPi = 6.283185307179586476925286766559;
  const int MAX_SIZE = 10*samplesPerSecond;

  double wave[MAX_SIZE];
  int index = 0;
}

using namespace Config;

bool write(int where, double what) {
  if (where<MAX_SIZE) {
    wave[where] += what;
    index = max(index, where);
    return true;
  } 
  return false;
}

void normalizeTo1(){
  const double verySmall = 0.0000000000001;
  double maxAmplitude = 0;
  for (int i=0; i<index; i++)
    maxAmplitude = max(maxAmplitude, abs(wave[i]));
  if (maxAmplitude>verySmall)
    for (int i=0; i<index; i++)
      wave[i] = wave[i] / maxAmplitude;
}

void waveToFile(ofstream& file) {
  const double maxAmplitude = 32767;  
  normalizeTo1();  
  for (int i = 0; i <index; i++) 
     writeWord(file, (int)(wave[i]*maxAmplitude), 2);
}

// (We'll generate a single C4 note with a sine wave, fading from left to right)
void exampleSine(ofstream& file, const double maxAmplitude) {
  const double c4Frequency = 261.626;  
  const double frequency = c4Frequency;
  const double seconds   = 2.5; 
  int numberOfSamples = seconds * samplesPerSecond;  
  for (int i = 0; i < numberOfSamples; i++) {
    double amplitude = (double)i / numberOfSamples * maxAmplitude;
    double value     = sin( twoPi * i * frequency / samplesPerSecond );
    writeWord(file, (int)(                amplitude  * value), 2);
    writeWord(file, (int)((maxAmplitude - amplitude) * value), 2);
  }
}

void sine(ofstream& file, const int length, const double amplitude) {
  for (int i = 0; i < length; i++) {
    double standarizedValue     = sin( twoPi * i/length );
    int value = 1.0 * amplitude * standarizedValue;
    for (int j = 0; j < 2; j++)
      writeWord(file, value, 2);
  }  
}

void writeHeader(ofstream& file) {
  file << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  writeWord( file,     16, 4 );  // no extension data
  writeWord( file,      1, 2 );  // PCM - integer samples
  writeWord( file, numberOfChannels, 2 );  
  writeWord( file, samplesPerSecond, 4 );  
  writeWord( file, samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
  writeWord( file, numberOfChannels * bytesPerSample, 2 );  // data block size 
  writeWord( file, bitsPerSample, 2 );  
}

void writeSamples(ofstream& file) {
  const double maxAmplitude = 32767;  
  //  exampleSine(file, maxAmplitude);
  for (int i = 0; i<3000; i++) {
    int amplitude = rand() % (int)maxAmplitude;
    int length = rand() % 500;
    sine(file, length, amplitude);
  }  
}

void init(){
  srand (time(NULL));
  for (i = 1; i < MAX_SIZE; i++)
     wave[i] = 0.0;
}

int main() {
  init();
 
  ofstream file( "example.wav", ios::binary );
  writeHeader(file);

  // Write the data chunk header
  size_t dataChunkPos = file.tellp();
  file << "data----";  // (chunk size to be filled in later)
  
  writeSamples(file);
  waveToFile(file);

  size_t fileLength = file.tellp();

  // Fix the data chunk header to contain the data size
  file.seekp( dataChunkPos + 4 );
  writeWord( file, fileLength - dataChunkPos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  file.seekp( 0 + 4 );
  writeWord( file, fileLength - 8, 4 ); 
}

