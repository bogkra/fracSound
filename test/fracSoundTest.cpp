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

TEST_F(fracSoundTest, trivialFractal) {
  Range xs(0, 100);
  Range ys(0.0, 123.456);
  Box box(xs, ys);
  Wave wave;
  vector<Box> parts;
  Fractal fractal(wave, box, parts);
  fractal.run(box, 0);
  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_TRUE(abs(wave.getSamples()[25] - 0.25) < small);
  ASSERT_TRUE(abs(wave.getSamples()[50] - 0.50) < small);
  ASSERT_TRUE(abs(wave.getSamples()[75] - 0.75) < small);
  ASSERT_TRUE(abs(wave.getSamples()[100] -1.00) < small);
}


TEST_F(fracSoundTest, level1Fractal) {
  Range xs(0, 100);
  Range ys(0.0, 1.0);
  Box box(xs, ys);
  Wave wave;

  Range exampleX(0.4, 0.8);
  Range exampleY(0.2, 0.5);
  Box exampleBox(exampleX, exampleY);

  Parts parts;
  parts.push_back(exampleBox);
  Fractal fractal(wave, box, parts);
  fractal.run(box, 1);
//  wave.normalize();
  ASSERT_EQ(wave.getSamples()[0], 0.0);
  ASSERT_EQ(wave.getSamples()[20], 0.1);
  ASSERT_EQ(wave.getSamples()[40], 0.2);
  ASSERT_EQ(wave.getSamples()[60], 0.35); 
  ASSERT_EQ(wave.getSamples()[80], 0.5);  
//  ASSERT_EQ(wave.getSamples()[99], 1.0);  // 0.0
//  ASSERT_TRUE(abs(wave.getSamples()[20] - 0.1) < small);
}


TEST_F(fracSoundTest, incrementatorTest) {
  int x = 0;
  for (Incrementator i; i.repeat(10);) 
      x +=3;
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
