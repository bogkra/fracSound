#pragma once


class Accumulator 
{
public:
  Accumulator() : value_(0) {};

  Accumulator& operator++ ();
  Accumulator operator++ (int);
  Accumulator operator+= (int i);
  Accumulator operator+= (Accumulator a);
  Accumulator operator=  (int  i);
  Accumulator operator+  (int i);
  Accumulator operator+ (Accumulator const& accu) const;
  friend Accumulator operator+ (int i, Accumulator accu) {
    return accu + i;
  };
  bool operator== (const int & i);
  bool operator< (const int & i);
//  int& operator& ();
  int getValue() const {return value_;};

private:
  int value_;
};






