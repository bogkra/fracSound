#pragma once


namespace Channels {
  const int mono = 1;
  const int stereo = 2;
  const int surround = 5 + 1 ;
}

enum Position {
  leftPos,
  rightPos
};


namespace Config {
  const int numberOfChannels = Channels::stereo ;  
  const int bytesPerSample = 2;
  const int bitsPerSample = 8 * bytesPerSample;
  const int samplesPerSecond = 44100;
  constexpr double pi = acos(-1);
  const int MAX_NO_SAMPLES = 2 * samplesPerSecond;
  const std::vector<Position> positions = {Position::leftPos, Position::rightPos};
}

