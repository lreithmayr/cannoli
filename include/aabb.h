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
	m_pMin(std::min(p1.getX(), p2.getX()), std::min(p1.getY(), p2.getY()), std::min(p1.getZ(), p2.getZ())),
	m_pMax(std::max(p1.getX(), p2.getX()), std::max(p1.getY(), p2.getY()), std::max(p1.getZ(), p2.getZ())) {};

  PointXYZ getPMin() {
	return m_pMin;
  }

  PointXYZ getPMax() {
	return m_pMax;
  }

  bool computeAABBIntersection(const LightRay &ray, float t_min, float t_max);

  bool isInside(PointXYZ &pt);

  cannoli::AABB expand(Vec3f &pt);

 private:
  PointXYZ m_pMin, m_pMax;
};
} // namespace cannoli
#endif //CANNOLI_SRC_BOUNDING_BOX_H_
