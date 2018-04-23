#include <gtest/gtest.h>
#include "fracSound.hpp"

using namespace std;

class fracSoundTest : public ::testing::Test
{
public:
};



TEST_F(fracSoundTest, zero)
{
  double small = 0.0000001;
  Wave wave;
  wave.sine(0, 100, 123.456);
  wave.normalize();
  ASSERT_EQ(wave.samples[0], 0.0);
  ASSERT_TRUE(abs(wave.samples[25] - 1.0) < small);
  ASSERT_TRUE(abs(wave.samples[50] - 0.0) < small);
  ASSERT_TRUE(abs(wave.samples[75] + 1.0) < small);
}

