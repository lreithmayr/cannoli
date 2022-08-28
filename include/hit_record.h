#ifndef CANNOLI_INCLUDE_HIT_RECORD_H_
#define CANNOLI_INCLUDE_HIT_RECORD_H_

#include "vec3f.h"
#include "point.h"

namespace cannoli {
  struct HitRecord {
	PointXYZ hit_point;
	Vec3f surf_normal;
	float t {};
  };
} // namespace cannoli
#endif //CANNOLI_INCLUDE_HIT_RECORD_H_
