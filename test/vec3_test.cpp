#include <gtest/gtest.h>
#include <vec3.h>

class Vec3Test : public ::testing::Test {
 protected:
  void SetUp() override {
	vec0 = *pVec0;
	vec1 = *pVec1;
  }
  void TearDown() override {
	delete pVec0;
	delete pVec1;
  }

  Cannoli::Vec3* pVec0 = new Cannoli::Vec3();
  Cannoli::Vec3* pVec1 = new Cannoli::Vec3(1.0, 2.0, 44.5674);
  Cannoli::Vec3 vec0;
  Cannoli::Vec3 vec1;
};

TEST_F(Vec3Test, InitsToZero) {
  EXPECT_FLOAT_EQ(vec0[0], 0);
  EXPECT_FLOAT_EQ(vec0[1], 0);
  EXPECT_FLOAT_EQ(vec0[2], 0);
}

TEST_F(Vec3Test, InitsManually) {
  EXPECT_FLOAT_EQ(vec1[0], 1.0);
  EXPECT_FLOAT_EQ(vec1[1], 2.0);
  EXPECT_FLOAT_EQ(vec1[2], 44.5674);
}
