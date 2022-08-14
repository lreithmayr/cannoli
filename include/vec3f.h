#ifndef CANNOLI_INCLUDE_VEC3F_H_
#define CANNOLI_INCLUDE_VEC3F_H_

namespace Cannoli {
  class Vec3f {
   public:
	Vec3f() : e_{0, 0, 0} {}
	Vec3f(float e0, float e1, float e2) : e_{e0, e1, e2} {}

	float operator[](const int i) const { return e_[i]; }
	Vec3f operator*(const float &f) { return {e_[0] * f, e_[1] * f, e_[2] * f}; }
	Vec3f operator*(const Vec3f &vec) { return {e_[0] * vec[0], e_[1] * vec[1], e_[2] * vec[2]}; }

   protected:
	float e_[3];
  };
}
#endif //CANNOLI_INCLUDE_VEC3F_H_
