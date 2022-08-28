#ifndef CANNOLI_INCLUDE_HIT_RECORD_H_
#define CANNOLI_INCLUDE_HIT_RECORD_H_

#include "vec3f.h"
#include "point.h"

namespace cannoli {
  struct HitRecord {
	PointXYZ hit_point;
	Vec3f surface_normal;
	float t {};
	bool front_face = false;
  };
} // namespace cannoli
#endif //CANNOLI_INCLUDE_HIT_RECORD_H_
