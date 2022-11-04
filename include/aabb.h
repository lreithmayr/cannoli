#ifndef CANNOLI_SRC_BOUNDING_BOX_H_
#define CANNOLI_SRC_BOUNDING_BOX_H_

#include "point.h"
#include "vec3f.h"
#include "light_ray.h"
#include "hit_record.h"

#include <algorithm>

namespace cannoli {
class AABB {
 public:
  AABB() {
	float minNum = std::numeric_limits<float>::lowest();
	float maxNum = std::numeric_limits<float>::max();
	m_pMin = PointXYZ(maxNum, maxNum, maxNum);
	m_pMax = PointXYZ(minNum, minNum, minNum);
  };
  explicit AABB(const PointXYZ &p1, const PointXYZ &p2) :
	m_pMin(std::min(p1.GetX(), p2.GetX()), std::min(p1.GetY(), p2.GetY()), std::min(p1.GetZ(), p2.GetZ())),
	m_pMax(std::max(p1.GetX(), p2.GetX()), std::max(p1.GetY(), p2.GetY()), std::max(p1.GetZ(), p2.GetZ())) {};

  bool AABBIntersection(const LightRay &ray, float t_min, float t_max);
 private:
  PointXYZ m_pMin{}, m_pMax{};
};
} // namespace cannoli
#endif //CANNOLI_SRC_BOUNDING_BOX_H_
