#include <gtest/gtest.h>
#include <vec3.h>

class Vec3Test : public ::testing::Test {
 protected:
  Cannoli::Vec3 vec;
};

TEST_F(Vec3Test, InitsToZero) {
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 0);
  EXPECT_EQ(vec[2], 0);
}
