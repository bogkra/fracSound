#pragma once
#include <vector>
#include <functional>

class Incrementator {
protected:
  int value_ {0};
public:
  Incrementator& operator++ ();
  Incrementator operator++ (int);
  bool repeat(const int end);
  operator int() const {return value_;};
};

void operator * (const int upperBound, std::function<void (void)> repeatedFunction) ;
void operator * (const int upperBound, std::function<void (const int)> repeatedFunction) ;

//w noworudzkiej 
