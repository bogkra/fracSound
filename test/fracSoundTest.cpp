#include <gtest/gtest.h>
#include <array>
#include "Wave.hpp"
#include "Incrementator.hpp"

using namespace std;

class fracSoundTest : public ::testing::Test
{
public:
  double small = 0.003;
};



TEST_F(fracSoundTest, sine)
{
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


TEST_F(fracSoundTest, twoSines)
{
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

TEST_F(fracSoundTest, incrementatorTest)
{
  int x = 0;
  for (Incrementator i; i.repeat(10);) 
      x +=3;
  ASSERT_EQ(x, 30);

}

TEST_F(fracSoundTest, repeatTest)
{
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
