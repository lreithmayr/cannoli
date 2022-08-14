#include <gtest/gtest.h>
#include <vec3f.h>

class Vec3fTest : public ::testing::Test {
 protected:
  void TearDown() override {
	delete pVec0;
	delete pVec1;
	delete pVec2;
  }

  Cannoli::Vec3f* pVec0 = new Cannoli::Vec3f();
  Cannoli::Vec3f* pVec1 = new Cannoli::Vec3f(1.0, 2.0, 3.5);
  Cannoli::Vec3f* pVec2 = new Cannoli::Vec3f(2.0, 5.0, 7.23455);

  Cannoli::Vec3f vec0 = *pVec0;
  Cannoli::Vec3f vec1 = *pVec1;
  Cannoli::Vec3f vec2 = *pVec2;
};

TEST_F(Vec3fTest, InitsToZero) {
  EXPECT_FLOAT_EQ(vec0[0], 0);
  EXPECT_FLOAT_EQ(vec0[1], 0);
  EXPECT_FLOAT_EQ(vec0[2], 0);
}

TEST_F(Vec3fTest, InitsManually) {
  EXPECT_FLOAT_EQ(vec1[0], 1.0);
  EXPECT_FLOAT_EQ(vec1[1], 2.0);
  EXPECT_FLOAT_EQ(vec1[2], 3.5);
}

TEST_F(Vec3fTest, FloatMultiplication) {
  float f = 3.0;
  Cannoli::Vec3f vec_fm = vec1 * f;

  EXPECT_FLOAT_EQ(vec_fm[0], vec1[0] * f);
  EXPECT_FLOAT_EQ(vec_fm[1], vec1[1] * f);
  EXPECT_FLOAT_EQ(vec_fm[2], vec1[2] * f);
}

TEST_F(Vec3fTest, VecMultiplication) {
  Cannoli::Vec3f vec_vm = vec1 * vec2;

  EXPECT_FLOAT_EQ(vec_vm[0], vec1[0] * vec2[0]);
  EXPECT_FLOAT_EQ(vec_vm[1], vec1[1] * vec2[1]);
  EXPECT_FLOAT_EQ(vec_vm[2], vec1[2] * vec2[2]);
}
