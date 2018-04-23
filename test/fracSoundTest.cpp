#include <gtest/gtest.h>
#include "fracSound.hpp"

using namespace std;

class fracSoundTest : public ::testing::Test
{
public:
};



TEST_F(fracSoundTest, zero)
{
  double small = 0.001;
  Wave wave;
  wave.samples.fill(0.0);
  wave.sine(100, 123.456);
  wave.normalize();
  ASSERT_EQ(wave.samples[0], 0.0);
  ASSERT_TRUE(abs(wave.samples[50] - 0.0) < small);
  ASSERT_EQ(wave.samples[25],  1.0);
  ASSERT_TRUE(abs(wave.samples[75] + 1.0) < small);
}

