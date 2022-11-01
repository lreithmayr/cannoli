#ifndef CANNOLI_INCLUDE_HIT_RECORD_H_
#define CANNOLI_INCLUDE_HIT_RECORD_H_

#include "vec3f.h"
#include "point.h"

namespace cannoli {
struct HitRecord {
  PointXYZ hit_point;
  Vec3f surface_normal;
  int id{0};
  float t{};
  float closest{};
  bool front_face = false;
  float u{};
  float v{};
};
} // namespace cannoli
#endif //CANNOLI_INCLUDE_HIT_RECORD_H_
