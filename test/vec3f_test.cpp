#include <gtest/gtest.h>
#include <vec3f.h>

class Vec3fTest : public ::testing::Test {
 protected:
  void TearDown() override {
	delete pVec1;
	delete pVec2;
  }

  cannoli::Vec3f *pVec1 = new cannoli::Vec3f(1.0, 7.0, 3.5);
  cannoli::Vec3f *pVec2 = new cannoli::Vec3f(2.0, 5.0, 7.23);

  cannoli::Vec3f vec1 = *pVec1;
  cannoli::Vec3f vec2 = *pVec2;
};

TEST_F(Vec3fTest, InitsToZero) {
  cannoli::Vec3f vec;

  EXPECT_FLOAT_EQ(vec.x(), 0);
  EXPECT_FLOAT_EQ(vec.y(), 0);
  EXPECT_FLOAT_EQ(vec.z(), 0);
}

TEST_F(Vec3fTest, InitsManually) {
  cannoli::Vec3f vec(1.0, 7.0, 3.5);

  EXPECT_FLOAT_EQ(vec.x(), 1.0);
  EXPECT_FLOAT_EQ(vec.y(), 7.0);
  EXPECT_FLOAT_EQ(vec.z(), 3.5);
}

TEST_F(Vec3fTest, FloatMultiplication) {
  float f = 3.0;
  cannoli::Vec3f vec_fm = vec1 * f;

  EXPECT_FLOAT_EQ(vec_fm[0], vec1[0] * f);
  EXPECT_FLOAT_EQ(vec_fm[1], vec1[1] * f);
  EXPECT_FLOAT_EQ(vec_fm[2], vec1[2] * f);
}

TEST_F(Vec3fTest, VecMultiplication) {
  cannoli::Vec3f vec_vm = vec1 * vec2;

  EXPECT_FLOAT_EQ(vec_vm[0], vec1[0] * vec2[0]);
  EXPECT_FLOAT_EQ(vec_vm[1], vec1[1] * vec2[1]);
  EXPECT_FLOAT_EQ(vec_vm[2], vec1[2] * vec2[2]);
}

TEST_F(Vec3fTest, VecAddition) {
  cannoli::Vec3f vec_add = vec1 + vec2;

  EXPECT_FLOAT_EQ(vec_add[0], vec1[0] + vec2[0]);
  EXPECT_FLOAT_EQ(vec_add[0], 3.0);
  EXPECT_FLOAT_EQ(vec_add[1], vec1[1] + vec2[1]);
  EXPECT_FLOAT_EQ(vec_add[2], vec1[2] + vec2[2]);
}

TEST_F(Vec3fTest, VecNegation) {
  cannoli::Vec3f vec_neg = -vec1;

  EXPECT_FLOAT_EQ(vec_neg[0], -vec1[0]);
  EXPECT_FLOAT_EQ(vec_neg[0], -1.0);
  EXPECT_FLOAT_EQ(vec_neg[1], -vec1[1]);
  EXPECT_FLOAT_EQ(vec_neg[2], -vec1[2]);
}

TEST_F(Vec3fTest, VecSubtraction) {
  cannoli::Vec3f vec_sub = vec2 - vec1;

  EXPECT_FLOAT_EQ(vec_sub[0], vec2[0] - vec1[0]);
  EXPECT_FLOAT_EQ(vec_sub[1], vec2[1] - vec1[1]);
  EXPECT_FLOAT_EQ(vec_sub[1], -2.0);
  EXPECT_FLOAT_EQ(vec_sub[2], vec2[2] - vec1[2]);
}

TEST_F(Vec3fTest, VecLength) {
  cannoli::Vec3f vec_len(0.0, 7.0, 0.0);
  EXPECT_FLOAT_EQ(vec_len.length(), 7);
}

TEST_F(Vec3fTest, VecDot) {
  float vec_dot = vec1.dot(vec2);
  EXPECT_FLOAT_EQ(vec_dot, 62.305);
}

TEST_F(Vec3fTest, VecCross) {
  cannoli::Vec3f vec_cross = vec1.cross(vec2);
  EXPECT_FLOAT_EQ(vec_cross[0], vec1[1] * vec2[2] - vec1[2] * vec2[1]);
  EXPECT_FLOAT_EQ(vec_cross[1], vec1[2] * vec2[0] - vec1[0] * vec2[2]);
  EXPECT_FLOAT_EQ(vec_cross[2], vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}

TEST_F(Vec3fTest, VecNormalized) {
  cannoli::Vec3f vec1_normalized = vec1.normalize();
  EXPECT_FLOAT_EQ(vec1_normalized[0], vec1[0] * (1 / vec1.length()));
  EXPECT_FLOAT_EQ(vec1_normalized[1], vec1[1] * (1 / vec1.length()));
  EXPECT_FLOAT_EQ(vec1_normalized[2], vec1[2] * (1 / vec1.length()));
}
