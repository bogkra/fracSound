#include <gtest/gtest.h>
#include <vector>
#include "Wave.hpp"
#include "WaveFile.hpp"
#include "Incrementator.hpp"
#include "Fractal.hpp"

using namespace std;

//TODO output bitmap tests instead of Wave
//TODO input bitmap
//TODO neural network


class fracSoundTest : public ::testing::Test {
public: 
  const double small = 0.0000001;
};


TEST_F(fracSoundTest, sine) {
  Wave wave;
  Range xs(0, 100);
  Range ys(0.0, 123.456);
  Box box(xs, ys);
  wave.sine(box);

  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_TRUE(abs(wave.getSamples()[25].first - 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[50].first - 0.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[75].first + 1.0) < small);
}


TEST_F(fracSoundTest, twoSines) {
  Range xs1(0, 100);
  Range ys(0.0, 123.456);
  Box box1(xs1, ys);
  Wave wave;
  wave.sine(box1);

  Range xs2(100, 200);
  Box box2(xs2, ys);
  wave.sine(box2);

  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_TRUE(abs(wave.getSamples()[25].first - 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[50].first      ) < small);
  ASSERT_TRUE(abs(wave.getSamples()[75].first + 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[100].first      ) < small);
  ASSERT_TRUE(abs(wave.getSamples()[125].first - 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[150].first      ) < small);
  ASSERT_TRUE(abs(wave.getSamples()[175].first + 1.0) < small);
}

TEST_F(fracSoundTest, level0trivial) {
  Wave wave;
  Parts parts;
  Fractal fractal(wave, parts);
  fractal.start(0);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[25].first, 0.0);
  ASSERT_EQ(wave.getSamples()[50].first, 0.0);
  ASSERT_EQ(wave.getSamples()[100].first, 0.0);
}

TEST_F(fracSoundTest, level1trivial) {
  Wave wave;
  vector<Box> parts;
  Fractal fractal(wave, parts);
  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[25].first, 0.0);
  ASSERT_EQ(wave.getSamples()[50].first, 0.0);
  ASSERT_EQ(wave.getSamples()[100].first, 0.0);

//  ASSERT_TRUE(abs(wave.getSamples()[25].first - 0.0) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[50].first - 0.0) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[75].first - 0.0) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[100].first -0.0) < small);
}


TEST_F(fracSoundTest, level1FractalUsingParts) {

  Box exampleBox(Range(0.4, 0.8), Range(0.2, 0.5));

  Parts parts;
  parts.push_back(exampleBox);
  Wave wave;
  Fractal fractal(wave,  parts);
  fractal.start(1);
//  ASSERT_EQ(wave.getSamples()[40].first, 0.2);
  ASSERT_EQ(wave.getSamples()[60].first, 0.35); 
  ASSERT_EQ(wave.getSamples()[80].first, 0.5);  
//  ASSERT_EQ(wave.getSamples()[100].first, 1.0);  // 0.0
}


TEST_F(fracSoundTest, level1FractalUsingPartsDown) {

  Box exampleBox(Range(0.4, 0.8), Range(0.5, 0.2));

  Parts parts;
  parts.push_back(exampleBox);
  Wave wave;
  Fractal fractal(wave, parts);
  fractal.start(1);
//  ASSERT_EQ(wave.getSamples()[40].first, 0.5);  
  ASSERT_EQ(wave.getSamples()[60].first, 0.35); 
}

TEST_F(fracSoundTest, level1FractalUsingPoints) {
  Wave wave;
  Points points = {Point(0.4, 0.2), Point(0.8, 0.5)};
  Fractal fractal(wave, points);

  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[ 0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[ 1].first, 0.005);
  ASSERT_EQ(wave.getSamples()[ 2].first, 0.01);
  ASSERT_EQ(wave.getSamples()[20].first, 0.10);
  ASSERT_EQ(wave.getSamples()[40].first, 0.20);
  ASSERT_EQ(wave.getSamples()[60].first, 0.35); 
  ASSERT_EQ(wave.getSamples()[80].first, 0.50);  
  ASSERT_EQ(wave.getSamples()[81].first, 0.475);  
  ASSERT_EQ(wave.getSamples()[90].first, 0.25);  
  ASSERT_EQ(wave.getSamples()[100].first, 0.0);  
} 


TEST_F(fracSoundTest, below0) {
  Wave wave;
  Points points = {Point(0.5, -0.8)};
  Fractal fractal(wave, points);
  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[25].first, -0.4);
  ASSERT_EQ(wave.getSamples()[50].first, -0.8);
  ASSERT_EQ(wave.getSamples()[75].first, -0.4);
  ASSERT_EQ(wave.getSamples()[100].first, 0.0);  
}


TEST_F(fracSoundTest, level2) {
  Wave wave;
  Points points = {Point(0.5, 0.2)};
  Fractal fractal(wave, points);
  fractal.start(2);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[25].first, 0.2);
  ASSERT_EQ(wave.getSamples()[30].first, 0.2);
  ASSERT_EQ(wave.getSamples()[50].first, 0.2);
  ASSERT_EQ(wave.getSamples()[60].first, 0.2);
  ASSERT_EQ(wave.getSamples()[101].first, 0.0);  
}

TEST_F(fracSoundTest, incrementatorTest) {
  int x = 0;
  for (Incrementator i; i.repeat(10);) 
      x += 3;
  ASSERT_EQ(x, 30);
}

TEST_F(fracSoundTest, repeatTest) {
  int x = 0;
  for (Incrementator i; i.repeat(10);)
      x += 3;
  ASSERT_EQ(x, 30);

  x = 0;
  for (Incrementator i; i.repeat(10);)
    for (Incrementator j; j.repeat(10);)
      x += 3;
  ASSERT_EQ(x, 300);

  Incrementator i; 
  i++;
  i=i;
  ASSERT_EQ(i, 1);  
}


TEST_F(fracSoundTest, level1width1000) {
  Wave wave;
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.setPositions(Range(0,1000));
  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[250].first, 0.4);
  ASSERT_EQ(wave.getSamples()[500].first, 0.8);
  ASSERT_EQ(wave.getSamples()[1000].first, 0.0);  
}

TEST_F(fracSoundTest, level1power2) {
  Wave wave;
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.setPositions(Range(0,1000));
  fractal.setPower(2.0);
  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[250].first, 0.8);
  ASSERT_EQ(wave.getSamples()[500].first, 1.6);
  ASSERT_EQ(wave.getSamples()[750].first, 0.8);
  ASSERT_EQ(wave.getSamples()[1000].first, 0.0);  
}


TEST_F(fracSoundTest, level1moved) {
  Wave wave;
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.setPositions(Range(1000,2000));
  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[1000].first, 0.0);
  ASSERT_EQ(wave.getSamples()[1250].first, 0.4);
  ASSERT_EQ(wave.getSamples()[1500].first, 0.8);
  ASSERT_EQ(wave.getSamples()[2000].first, 0.0);  
}

TEST_F(fracSoundTest, panorama) {
  Wave wave;
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.setPositions(Range(1000,2000));
  fractal.setPanorama(Stereo(0.5, 0.5));
  fractal.start(1);
  ASSERT_EQ(wave.getSamples()[1000].first, 0.0);
  ASSERT_EQ(wave.getSamples()[1250].first, 0.2);
  ASSERT_EQ(wave.getSamples()[1500].first, 0.4);
  ASSERT_EQ(wave.getSamples()[2000].first, 0.0);  
}


double rand01() {
  const int big = 100000000;
  return (double)(rand() % big) / (double)big;
}

TEST_F(fracSoundTest, audibleTest) {
  Wave wave;
//  vector<Box> parts;
//  Points points = {Point(0.5, 0.8), Point(0.6, 0.1), Point(0.6746345, 1.121), Point(0.75858558, 0.3433)};
  10 * [&] {
    Points points;// = {Point(0.0123123, 0.2),  Point(0.175858558, 0.7433), Point(0.2444, -0.9767), Point(0.63, 0.99), Point(0.7646345, -0.98)};
    double x=0;
    for (int i = 0; x<1.0 and i<10; i++) {
      x += rand01() / 5.0;
      double amplitude = 1.0*rand01();    
      points.push_back(Point(x,amplitude));
//      cout << "  " << x << " a:" << amplitude;
    }
//  Points points = {Point(0.5, 0.9)};
    Fractal fractal(wave, points);
    int start = rand01()*80000;
    int end = start + rand01()*50000;  // 84000
    fractal.setPositions(Range(start, end));
    fractal.setPower(rand01());
    double left = rand01();
    double right = rand01();
    fractal.setPanorama(Stereo(left, right));
//    cout << " left= " << left << " right = " << right;
    fractal.start(5);
  };
  WaveFile waveFile("out.wav", &wave);
  ASSERT_EQ(true, true);
}

/*
TEST_F(fracSoundTest, level1file) {
  Wave wave;
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.start(1);
  WaveFile waveFile("out4.wav", &wave);
  ASSERT_EQ(wave.getSamples()[0].first, 0.0);
  ASSERT_EQ(wave.getSamples()[25].first, 0.4);
  ASSERT_EQ(wave.getSamples()[50].first, 0.8);
  ASSERT_EQ(wave.getSamples()[100].first, 0.0);  
}
*/


