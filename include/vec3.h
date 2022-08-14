#ifndef CANNOLI_INCLUDE_VEC3_H_
#define CANNOLI_INCLUDE_VEC3_H_

namespace Cannoli {
  class Vec3 {
   public:
	Vec3() : e_{0, 0, 0} {}
	Vec3(float e0, float e1, float e2) : e_{e0, e1, e2} {}

	float operator[](int i) { return e_[i]; }

   protected:
	float e_[3];
  };
}
#endif //CANNOLI_INCLUDE_VEC3_H_
