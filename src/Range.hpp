#pragma once

class Range {
public:
  Range() {};
  Range(const double begin, const double end) : begin_(begin), end_(end) {};
  double getBegin() const {return begin_;};
  double getEnd() const {return end_;};
  double length() const;
  bool isForward() const;
  double min() const;
  double max() const;
private:
  double begin_;  
  double end_;  
};


