#ifndef CANNOLI_INCLUDE_SPHERE_H_
#define CANNOLI_INCLUDE_SPHERE_H_

#include "object.h"

namespace cannoli {
  class Sphere : public Object {
   public:
	Sphere(Vec3f center, float radius) : m_center(center), m_radius(radius) {
	  m_type = SPHERE;
	}

	// Solves quadratic equation for a light ray with origin A, direction b and time constant t hitting a sphere with
	// given center C and radius r
	// t²*b*b + 2t*b*(A-C) + (A-C)*(A-C) - r² <= 0
	//  a_2 = b*b, a_1 = 2b*(A-C), a_0 = (A-C)(A-C) - r²
	bool Hit(const LightRay& ray) override;

   protected:
	PointXYZ m_center;
	float m_radius;
	Material m_material;
  };
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_SPHERE_H_
