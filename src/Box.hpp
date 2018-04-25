#pragma once

class Box {
public:
  Box(const double x1, const double x2, const double y1, const double y2);
  double getX1() const {return x1_;};
  double getX2() const {return x2_;};
  double getY1() const {return y1_;};
  double getY2() const {return y2_;};
  double width() const;
  double height() const;
  bool isForward() const;
private:
  double x1_;  
  double x2_;  
  double y1_;  
  double y2_;  
};


