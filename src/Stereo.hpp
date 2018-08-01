#pragma once

class Stereo { 
public:
  Stereo() {};
  Stereo(const double & l, const double & r) : left(l), right(r) {};
  double left = 1.0;
  double right = 1.0;
};

