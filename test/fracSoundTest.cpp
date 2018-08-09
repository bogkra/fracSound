#include <gtest/gtest.h>
#include <vector>
#include <ctime>
#include <chrono>
#include "Wave.hpp"
#include "WaveFile.hpp"
#include "Incrementator.hpp"
#include "Fractal.hpp"
#define test(x, value)   ASSERT_EQ(wave.getSamples()[x].left,  value);  ASSERT_EQ(wave.getSamples()[x].right, value);
#define dirtyTest(x,value)  ASSERT_TRUE(abs(wave.getSamples()[x].left  - value) < small);  ASSERT_TRUE(abs(wave.getSamples()[x].right - value) < small);

using namespace std;

//TODO output bitmap tests instead of Wave
//TODO input bitmap
//TODO neural network


class fracSoundTest : public ::testing::Test {
public: 
  const double small = 0.0000001;
  Wave wave;
  Points points;

  void start() {
  };
  
//  Fractal & fractal(wave, points);

  //Fractal fractal0;

//  Points points = {Point(0.5, -0.8)};
//  Fractal fractal(wave, points);
//  fractal.start(1);
};

//void test(Wave & wave, const int x, const double & value) {
//  ASSERT_EQ(wave.getSamples()[x].left,  value);
//  ASSERT_EQ(wave.getSamples()[x].right, value);
//}

//void dirtyTest(Wave & wave, const int x, const double & value) {
//  const double small = 0.0000001;
//  ASSERT_TRUE(abs(wave.getSamples()[x].left  - value) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[x].right - value) < small);
//}

TEST_F(fracSoundTest, sine) {
  Wave wave;
  Range xs(0, 100);
  Range ys(0.0, 123.456);
  Box box(xs, ys);
  wave.sine(box, Stereo(1,1));

  wave.normalize();
  test( 0, 0.0);
  dirtyTest( 25, 1.0);
  dirtyTest( 50, 0.0);
  dirtyTest( 75,-1.0);
}

TEST_F(fracSoundTest, twoSines) {
  Range xs1(0, 100);
  Range ys(0.0, 123.456);
  Box box1(xs1, ys);
  Wave wave;
  wave.sine(box1, Stereo(1,1));

  Range xs2(100, 200);
  Box box2(xs2, ys);
  wave.sine(box2, Stereo(1,1));

  wave.normalize();
  test(   0, 0.0);
  dirtyTest(  25, 1.0);
  dirtyTest(  50, 0.0);
  dirtyTest(  75,-1.0);
  dirtyTest( 100, 0.0);
  dirtyTest( 125, 1.0);
  dirtyTest( 150, 0.0);
  dirtyTest( 175,-1.0);
}

TEST_F(fracSoundTest, level0trivial) {
  Wave wave;
  Parts parts;
  Fractal fractal(wave, parts);
  fractal.start(0);
  test( 0, 0.0);
  test( 25, 0.0);
  test( 50, 0.0);
  test( 100, 0.0);
}

TEST_F(fracSoundTest, level1trivial) {
  Wave wave;
  vector<Box> parts;
  Fractal fractal(wave, parts);
  fractal.start(1);
  test( 0, 0.0);
  test( 25, 0.0);
  test( 50, 0.0);
  test( 100, 0.0);
}


TEST_F(fracSoundTest, level1FractalUsingParts) {

  Box exampleBox(Range(0.4, 0.8), Range(0.2, 0.5));

  Parts parts;
  parts.push_back(exampleBox);
  Wave wave;
  Fractal fractal(wave,  parts);
  fractal.start(1);
//  ASSERT_EQ(wave.getSamples()[40].left, 0.2);
  test( 60, 0.35);
  test( 80, 0.5);
//  ASSERT_EQ(wave.getSamples()[100].left, 1.0);  // 0.0
}


TEST_F(fracSoundTest, level1FractalUsingPartsDown) {

  Box exampleBox(Range(0.4, 0.8), Range(0.5, 0.2));

  Parts parts;
  parts.push_back(exampleBox);
  Wave wave;
  Fractal fractal(wave, parts);
  fractal.start(1);
//  ASSERT_EQ(wave.getSamples()[40].left, 0.5);  
  test( 60, 0.35);
}

TEST_F(fracSoundTest, level1FractalUsingPoints) {
  Wave wave;
  Points points = {Point(0.4, 0.2), Point(0.8, 0.5)};
  Fractal fractal(wave, points);

  fractal.start(1);
  test(   0, 0.0);
  test(   1, 0.005);
  test(   2, 0.01);
  test(  20, 0.10);
  test(  40, 0.20);
  test(  60, 0.35);
  test(  80, 0.50);
  test(  81, 0.475);
  test(  90, 0.25);
  test( 100, 0.0);
} 


TEST_F(fracSoundTest, below0) {
  Wave wave;
  Points points = {Point(0.5, -0.8)};
  Fractal fractal(wave, points);
  fractal.start(1);
  test(   0,  0.0);
  test(  25, -0.4);
  test(  50, -0.8);
  test(  75, -0.4);
  test( 100,  0.0);
}


TEST_F(fracSoundTest, level2) {
  Wave wave;
  Points points = {Point(0.5, 0.2)};
  Fractal fractal(wave, points);
  fractal.start(2);
  test(   0,  0.0);
  test(  25,  0.2);
  test(  30,  0.2);
  test(  50,  0.2);
  test(  60,  0.2);
  test( 101,  0.0);
}

TEST_F(fracSoundTest, level3) {
  Wave wave;
  Points points = {Point(0.5, 0.2)};
  Fractal fractal(wave, points);
  fractal.start(3);

  ASSERT_EQ(wave.getSamples()[  0].left,  0);
  ASSERT_EQ(wave.getSamples()[ 25].left,0.2);
  ASSERT_EQ(wave.getSamples()[ 37].left,0.25);
  ASSERT_EQ(wave.getSamples()[ 50].left,0.2);
  ASSERT_EQ(wave.getSamples()[100].left,  0);

  test(   0,  0.0);
  test(  25,  0.2);
  test(  37,  0.25);
  test(  50,  0.2);
  test( 101,  0.0);

}

TEST_F(fracSoundTest, incrementatorTest) {
  int x = 0;
  int j = 0;
  for (Incrementator i; i.repeat(10);) {
    x += 3;
    j = i;
  }
  ASSERT_EQ(x, 30);
  ASSERT_EQ(j, 10);
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
  Fractal fractal(wave);  
  fractal.setPoints({Point(0.5, 0.8)});
  fractal.setPositions(Range(0,1000));
  fractal.start(1);
  test(   0,  0.0);
  test( 250,  0.4);
  test( 500,  0.8);
  test(1000,  0.0);
}

TEST_F(fracSoundTest, level1power2) {
  Wave wave;
  Fractal fractal(wave);
  fractal.setPoints({Point(0.5, 0.8)});
  fractal.setPositions(Range(0,1000));
  fractal.setPower(2.0);
  fractal.start(1);
  test(   0,  0.0);
  test( 250,  0.8);
  test( 500,  1.6);
  test( 750,  0.8);
  test(1000,  0.0);
}


TEST_F(fracSoundTest, level1moved) {
  Wave wave;
  Fractal fractal(wave);  
  fractal.setPoints({Point(0.5, 0.8)});
  fractal.setPositions(Range(1000,2000));
  fractal.start(1);
  test(1000,  0.0);
  test(1250,  0.4);
  test(1500,  0.8);
  test(1750,  0.4);
  test(2000,  0.0);
}

TEST_F(fracSoundTest, panorama) {
  Wave wave;
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.setPositions(Range(1000,2000));
  fractal.setPanorama(Stereo(0.5, 0.5));
  fractal.start(1);
  test(1000,  0.0);
  test(1250,  0.2);
  test(1500,  0.4);
  test(2000,  0.0);
}

TEST_F(fracSoundTest, isBetween) {
  ASSERT_TRUE (Range(0, 2).isBetween(1)); 
}

TEST_F(fracSoundTest, intoBoundaries) {
  double x = 3.0;
  Range(0, 2).intoBoundaries(x);
  ASSERT_EQ(x, 2);
}

TEST_F(fracSoundTest, rangeLength) {
  Range r(40,55);
  ASSERT_EQ(r.length(), 15);
}

TEST_F(fracSoundTest, boxWidth) {
  Range x(40,55);
  Range y(10,55);
  Box b(x,y);
   
  ASSERT_EQ(b.width(), 15);
  ASSERT_EQ(b.height(), 45);
}

double rand01() {
  const int big = 100000000;
  return (double)(rand() % big) / (double)big;
}

TEST_F(fracSoundTest, audibleTest) {
  Wave wave;
//  vector<Box> parts;
//  Points points = {Point(0.5, 0.8), Point(0.6, 0.1), Point(0.6746345, 1.121), Point(0.75858558, 0.3433)};
  
  std::clock_t c_start = std::clock();
  auto t_start = std::chrono::high_resolution_clock::now();  
  
  if (true) {
  const int howManyTimes = 40;
  const int depth = 3;
  howManyTimes * [&] {
    Points points;
   // TODO : examples, not random but REPEAT! = {Point(0.0123123, 0.2),  Point(0.175858558, 0.7433), Point(0.2444, -0.9767), Point(0.63, 0.99), Point(0.7646345, -0.98)};
    
    double x=0;
    for (int i = 0; x<1.0 and i<11; i++) {
//      x += (rand01() + rand01() + rand01() )  / 10.0;
      x += 0.001 + (rand01() )  / 8.0;
      const double maximum = 0.803;
      double amplitude = maximum * (2.0*rand01() - 1.0);    
      points.push_back(Point(x,amplitude));
    }
    Fractal fractal(wave, points);
//    fractal.setLineFunction(&Wave::sine);
    int start = rand01()*80000;
    int end = start + 1 + (rand01() + rand01())*2500;  // 84000
    fractal.setPositions(Range(start, end));
    fractal.setPower(rand01());
    double left = rand01();
    double right = rand01();
    fractal.setPanorama(Stereo(left, right));
    fractal.start(depth);

    int diff = end - start;

    10 * [&]() {
      start += diff;
      end += diff;
      fractal.setPositions(Range(start, end));
      fractal.start(depth);
    };

  };
  std::clock_t c_end = std::clock();
  auto t_end = std::chrono::high_resolution_clock::now();
 
  std::cout << std::fixed << std::setprecision(5) << "CPU time used: "
            << 1000.0*(c_end-c_start) / CLOCKS_PER_SEC / howManyTimes << " ms\n"
            << "Wall clock time passed: "
            << std::chrono::duration<double, std::milli>(t_end-t_start).count() / howManyTimes
            << " ms\n";
  }
  else {
    const int length = 100;
    const int depth = 5	;
    Points points = { Point(0.11231, 0.7), 
                      Point(0.4561, -0.3), 
                      Point(0.4571, 0.7343), 
 		      Point(0.8571, -0.7343), 
                      Point(0.8771, -0.1343),  
                      Point(0.9571, 0.7343),
                      Point(0.9871, 0.7343),
                      Point(0.9971, 0.7343)
    };
//    Points points = {Point(0.5, 0.7) };
    Fractal fractal(wave, points);
    fractal.setLineFunction(&Wave::halfSine);
    for (int i=0; i< 87000; i+=length) {
/*      Range xs(i, i+length);
      Range ys(1, -1);
      Box box(xs, ys);
      wave.sine(box);*/
      fractal.setPositions(Range(i, i+length));

      fractal.start(depth);
    }
    wave.normalize();
  }
 
  WaveFile waveFile("out.wav", &wave);
  ASSERT_EQ(true, true);
}

