#include "fracSound.hpp"


using namespace std;

#include <cmath>
#include <fstream>
#include <iostream>
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


int main() {
//http://www.cplusplus.com/user/Duthomhas/
  ofstream f( "example.wav", ios::binary );

  int numberOfChannels = Channels::stereo ;  
  const int bytesPerSample = 2;
  const int bitesPerSample = 8*bytesPerSample;
  const int samplesPerSecond = 44100;

  // Write the file headers
  f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
  write_word( f,     16, 4 );  // no extension data
  write_word( f,      1, 2 );  // PCM - integer samples
  write_word( f, numberOfChannels, 2 );  
  write_word( f, samplesPerSecond, 4 );  
  write_word( f, samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
  write_word( f, numberOfChannels * bytesPerSample, 2 );  // data block size 
  write_word( f, bitesPerSample, 2 );  

  // Write the data chunk header
  size_t data_chunk_pos = f.tellp();
  f << "data----";  // (chunk size to be filled in later)
  
  // Write the audio samples
  // (We'll generate a single C4 note with a sine wave, fading from left to right)
  const double two_pi = 6.283185307179586476925286766559;
  const double max_amplitude = 32760;  // "volume"

  double hz        = samplesPerSecond;    
  double frequency = 261.626;  // middle C
  double seconds   = 2.5;      // time

  int length = hz * seconds;  // total number of samples
  for (int i = 0; i < length; i++) {
    double amplitude = (double)i / length * max_amplitude;
    double value     = sin( (two_pi * i * frequency) / hz );
    write_word( f, (int)(                 amplitude  * value), 2 );
    write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
  }
  
  // (We'll need the final file size to fix the chunk sizes above)
  size_t file_length = f.tellp();

  // Fix the data chunk header to contain the data size
  f.seekp( data_chunk_pos + 4 );
  write_word( f, file_length - data_chunk_pos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  f.seekp( 0 + 4 );
  write_word( f, file_length - 8, 4 ); 
}
