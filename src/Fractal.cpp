#include <cmath>
#include <iostream>
#include <algorithm>
#include "Fractal.hpp"


using namespace std;

Fractal::Fractal(Wave & wave, const Parts parts) : wave_(wave), parts_(parts) {
}


Fractal::Fractal(Wave & wave,  const Points points) : wave_(wave), points_(points) {
  points_.insert(points_.begin(), Point(0,0)); 
  points_.push_back(Point(1.0, 0.0)); 
  for (auto it = points_.begin();  next(it) != points_.end(); it++) 
    pointToPart(it);
}

void Fractal::pointToPart(Points::iterator it) {
  Range times(it->first, next(it)->first); 
  Range amplitudes(it->second, next(it)->second); 
  Box tempBox(times, amplitudes);
  parts_.push_back(tempBox); 
}


void Fractal::run(const Box & outsideBox, const int level) {

  Box drawBox = outsideBox;
  drawBox.widthRescale(100.0);    
  cout << drawBox.getXRange().getBegin() << "," << drawBox.getYRange().getBegin() << " ->  ";
  cout << drawBox.getXRange().getEnd() << "," << drawBox.getYRange().getEnd() << "   "; 
  wave_.line(drawBox);
//  if (level == 0) {
//  }
//  else 
  if (level > 0) {
    for (auto part : parts_) {    
//      wave_.line(outsideBox);  //???
    


      Box newBox = part;
//      cout << "a:" << part.width() << " b:" << outsideBox.width() << "   ";
//      newBox.equallyRescale(part.width()/outsideBox.width()); 
      double alpha = part.width()/outsideBox.width();
      cout << "alpha=" << alpha << "   ";
   //   newBox.rescale(outsideBox);


//      newBox.getYRange().rescale(alpha);  // to w ogole nie dziala! // x tez przeskalowac !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      run(newBox, level - 1);
    }
  }
}

void Fractal::start(const int level) {
  Box box(Range(0,1), Range(0,0)); 
  run(box, level);
}

//skandynawska w rynku (w paryzu??)

//12-13
// 09881

//opel klasa b 50 - przygotowawcza o 20 
//od 8 do 18
