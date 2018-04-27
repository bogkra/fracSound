#include <gtest/gtest.h>
#include "Wave.hpp"

using namespace std;

class fracSoundTest : public ::testing::Test
{
public:
  double small = 0.003;
};



TEST_F(fracSoundTest, sine)
{
  Wave* pWave = new(Wave);
  Wave wave = *pWave;
  Range xs(0, 100);
  Range ys(0.0, 123.456);
  Box box(xs, ys);
  wave.sine(box);

  wave.normalize();
  ASSERT_EQ(wave.samples[0], 0.0);
  ASSERT_TRUE(abs(wave.samples[25] - 1.0) < small);
  ASSERT_TRUE(abs(wave.samples[50] - 0.0) < small);
  ASSERT_TRUE(abs(wave.samples[75] + 1.0) < small);
  delete(pWave);
}


TEST_F(fracSoundTest, twoSines)
{
  Wave* pWave = new(Wave);
  Wave wave = *pWave;
  Range xs1(0, 100);
  Range ys(0.0, 123.456);
  Box box1(xs1, ys);
  wave.sine(box1);

  Range xs2(100, 200);
  Box box2(xs2, ys);
  wave.sine(box2);

  wave.normalize();
  ASSERT_EQ(wave.samples[0], 0.0);
  ASSERT_TRUE(abs(wave.samples[25] - 1.0) < small);
  ASSERT_TRUE(abs(wave.samples[50]      ) < small);
  ASSERT_TRUE(abs(wave.samples[75] + 1.0) < small);
  ASSERT_TRUE(abs(wave.samples[100]      ) < small);
  ASSERT_TRUE(abs(wave.samples[125] - 1.0) < small);
  ASSERT_TRUE(abs(wave.samples[150]      ) < small);
  ASSERT_TRUE(abs(wave.samples[175] + 1.0) < small);
  delete(pWave);
}

