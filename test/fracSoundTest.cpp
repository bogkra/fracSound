#include <gtest/gtest.h>
#include <vector>
#include "Wave.hpp"
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
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_TRUE(abs(wave.getSamples()[25] - 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[50] - 0.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[75] + 1.0) < small);
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
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_TRUE(abs(wave.getSamples()[25] - 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[50]      ) < small);
  ASSERT_TRUE(abs(wave.getSamples()[75] + 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[100]      ) < small);
  ASSERT_TRUE(abs(wave.getSamples()[125] - 1.0) < small);
  ASSERT_TRUE(abs(wave.getSamples()[150]      ) < small);
  ASSERT_TRUE(abs(wave.getSamples()[175] + 1.0) < small);
}

TEST_F(fracSoundTest, level0trivial) {
  Wave wave;
  vector<Box> parts;
  Fractal fractal(wave, parts);
  fractal.start(0);
//  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_EQ(wave.getSamples()[25], 0.0);
  ASSERT_EQ(wave.getSamples()[50], 0.0);
  ASSERT_EQ(wave.getSamples()[100], 0.0);
}

TEST_F(fracSoundTest, level1trivial) {
  Wave wave;
  vector<Box> parts;
  Fractal fractal(wave, parts);
  fractal.start(1);
//  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_EQ(wave.getSamples()[25], 0.0);
  ASSERT_EQ(wave.getSamples()[50], 0.0);
  ASSERT_EQ(wave.getSamples()[100], 0.0);

//  ASSERT_TRUE(abs(wave.getSamples()[25] - 0.0) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[50] - 0.0) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[75] - 0.0) < small);
//  ASSERT_TRUE(abs(wave.getSamples()[100] -0.0) < small);
}

/*
TEST_F(fracSoundTest, level1FractalUsingParts) {

  Box box(  Range(0, 100),  Range(0.0, 1.0));
  Box exampleBox(Range(0.4, 0.8), Range(0.2, 0.5));

  Parts parts;
  parts.push_back(exampleBox);
  Wave wave;
  Fractal fractal(wave,  parts);
  fractal.run(box, 1);
//  wave.normalize();
//  ASSERT_EQ(wave.getSamples()[0], 0.0);
//  ASSERT_EQ(wave.getSamples()[20], 0.1);
//  ASSERT_EQ(wave.getSamples()[40], 0.2);
  ASSERT_EQ(wave.getSamples()[60], 0.35); 
  ASSERT_EQ(wave.getSamples()[80], 0.5);  
//  ASSERT_EQ(wave.getSamples()[100], 1.0);  // 0.0
}

TEST_F(fracSoundTest, level1FractalUsingPartsDown) {

  Box box(  Range(0, 100),  Range(0.0, 1.0));
  Box exampleBox(Range(0.4, 0.8), Range(0.5, 0.2));

  Parts parts;
  parts.push_back(exampleBox);
  Wave wave;
  Fractal fractal(wave, parts);
  fractal.run(box, 1);
//  ASSERT_EQ(wave.getSamples()[40], 0.5);  
  ASSERT_EQ(wave.getSamples()[60], 0.35); 
}

TEST_F(fracSoundTest, level1FractalUsingPoints) {
  Wave wave;
//  Box box(  Range(0, 100),  Range(0.0, 100));
  Points points = {Point(0.4, 0.2), Point(0.8, 0.5)};
  Fractal fractal(wave, points);

  fractal.start(1);
//  wave.normalize();
  ASSERT_EQ(wave.getSamples()[ 0], 0.0);
//  ASSERT_EQ(wave.getSamples()[ 1], 0.5);
//  ASSERT_EQ(wave.getSamples()[ 2], 1.0);
  ASSERT_EQ(wave.getSamples()[20], 0.10);
  ASSERT_EQ(wave.getSamples()[40], 0.20);
  ASSERT_EQ(wave.getSamples()[60], 0.35); 
  ASSERT_EQ(wave.getSamples()[80], 0.50);  
  ASSERT_EQ(wave.getSamples()[81], 0.475);  
  ASSERT_EQ(wave.getSamples()[90], 0.25);  
  ASSERT_EQ(wave.getSamples()[100], 0.0);  
} 
*/

TEST_F(fracSoundTest, level1) {
  Wave wave;
//  Box box(Range(0, 100),  Range(0.0, 1.0));
  Points points = {Point(0.5, 0.8)};
  Fractal fractal(wave, points);
  fractal.start(1);
//  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_EQ(wave.getSamples()[25], 0.4);
  ASSERT_EQ(wave.getSamples()[50], 0.8);
  ASSERT_EQ(wave.getSamples()[100], 0.0);  
}

/*
TEST_F(fracSoundTest, level2) {
  Wave wave;
//  Box box(Range(0, 100),  Range(0.0, 1.0));
  Points points = {Point(0.5, 0.2)};
  Fractal fractal(wave, points);
  fractal.start(2);
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_EQ(wave.getSamples()[25], 0.0);
  ASSERT_EQ(wave.getSamples()[50], 0.0);
  ASSERT_EQ(wave.getSamples()[101], 0.0);  
}
*/
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
