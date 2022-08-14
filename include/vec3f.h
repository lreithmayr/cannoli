#ifndef CANNOLI_INCLUDE_VEC3F_H_
#define CANNOLI_INCLUDE_VEC3F_H_

#include <iostream>
#include <cmath>

namespace Cannoli {
  class Vec3f {
   public:
	Vec3f() : e_{0, 0, 0} {}
	Vec3f(float e0, float e1, float e2) : e_{e0, e1, e2} {}

	float x() { return e_[0]; }
	float y() { return e_[1]; }
	float z() { return e_[2]; }

	float operator[](int i) const { return e_[i]; }
	Vec3f operator*(const float& f) { return {e_[0] * f, e_[1] * f, e_[2] * f}; }
	Vec3f operator*(const Vec3f& vec) { return {e_[0] * vec[0], e_[1] * vec[1], e_[2] * vec[2]}; }
	Vec3f operator+(const Vec3f& vec) { return {e_[0] + vec[0], e_[1] + vec[1], e_[2] + vec[2]}; }
	Vec3f operator-() { return {-e_[0], -e_[1], -e_[2]}; }
	Vec3f operator-(const Vec3f& vec) { return {e_[0] - vec[0], e_[1] - vec[1], e_[2] - vec[2]}; }
	friend std::ostream& operator<<(std::ostream& out, Vec3f& vec) {
	  return out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
	}

	float length() { return (std::sqrt(e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2])); }
	float dot(Vec3f& vec) { return (e_[0] * vec[0] + e_[1] * vec[1] + e_[2] * vec[2]); }
	Vec3f cross(Vec3f& vec) {
	  return {
		  e_[1] * vec[2] - e_[2] * vec[1],
		  e_[2] * vec[0] - e_[0] * vec[2],
		  e_[0] * vec[1] - e_[1] * vec[0]
	  };
	}
	Vec3f normalize() { return (*this * (1 / this->length())); }

   protected:
	float e_[3];
  };
}
#endif //CANNOLI_INCLUDE_VEC3F_H_
