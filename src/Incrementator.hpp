#pragma once

class Incrementator 
{
  int value_ {0};
public:
  Incrementator& operator++ ();
  Incrementator operator++ (int);
  bool times(const int end);
  operator int() const {return value_;};
};












