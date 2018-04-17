#include <cmath>
#include <fstream>
#include <iostream>
#include "fracSound.hpp"

using namespace std;

namespace little_endian_io {
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) ) {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}

using namespace little_endian_io;


namespace Channels {
  const int mono = 1;
  const int stereo = 2;
  const int surround = 5 + 1 ;
}

namespace Config {
  int numberOfChannels = Channels::stereo ;  
  const int bytesPerSample = 2;
  const int bitsPerSample = 8*bytesPerSample;
  const int samplesPerSecond = 44100;
}

using namespace Config;

// (We'll generate a single C4 note with a sine wave, fading from left to right)
void exampleSine(ofstream& file, const double maxAmplitude) {
  const double two_pi = 6.283185307179586476925286766559;
  const double hz        = samplesPerSecond;    
  const double frequency = 261.626;  // middle C
  const double seconds   = 2.5;      // time

  int length = hz * seconds;  // total number of samples
  for (int i = 0; i < length; i++) {
    double amplitude = (double)i / length * maxAmplitude;
    double value     = sin( two_pi * i * frequency / hz );
    write_word( file, (int)(                amplitude  * value), 2 );
    write_word( file, (int)((maxAmplitude - amplitude) * value), 2 );
  }
}

void sine(ofstream& file, const int length, const int amplitude) {
  const double two_pi = 6.283185307179586476925286766559;
  const double hz        = samplesPerSecond;    
  for (int i = 0; i < length; i++) {
    double standarizedValue     = sin( two_pi * i/length / hz );
    int value = amplitude * standarizedValue;
    for (int j = 1; j <= 2; j++)
      write_word(file, value, 2);
  }  
}

void writeHeader(ofstream& file) {
  file << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  write_word( file,     16, 4 );  // no extension data
  write_word( file,      1, 2 );  // PCM - integer samples
  write_word( file, numberOfChannels, 2 );  
  write_word( file, samplesPerSecond, 4 );  
  write_word( file, samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
  write_word( file, numberOfChannels * bytesPerSample, 2 );  // data block size 
  write_word( file, bitsPerSample, 2 );  
}

int main() {
//http://www.cplusplus.com/user/Duthomhas/
  ofstream file( "example.wav", ios::binary );
  writeHeader(file);

  // Write the data chunk header
  size_t data_chunk_pos = file.tellp();
  file << "data----";  // (chunk size to be filled in later)
  
  // Write the audio samples

  const double maxAmplitude = 32760;  // "volume"
  exampleSine(file, maxAmplitude);
 
  // (We'll need the final file size to fix the chunk sizes above)
  size_t file_length = file.tellp();

  // Fix the data chunk header to contain the data size
  file.seekp( data_chunk_pos + 4 );
  write_word( file, file_length - data_chunk_pos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  file.seekp( 0 + 4 );
  write_word( file, file_length - 8, 4 ); 
}
