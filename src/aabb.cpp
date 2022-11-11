#include "aabb.h"

bool cannoli::AABB::AABBIntersection(const LightRay &ray, float t_min, float t_max) {
  for (int a = 0; a < 3; a++) {
	auto inverse_dir = 1.0f / ray.GetDirection()[a];
	auto t0 = (m_pMin[a] - ray.GetOrigin()[a]) * inverse_dir;
	auto t1 = (m_pMax[a] - ray.GetOrigin()[a]) * inverse_dir;
	if (inverse_dir < 0.0f) {
	  std::swap(t0, t1);
	}
	t_min = (t0 > t_min) ? t0 : t_min;
	t_max = (t1 < t_max) ? t1 : t_max;
	if (t_max <= t_min) {
	  return false;
	}
  }
  return true;
}

bool cannoli::AABB::IsInside(cannoli::PointXYZ &pt) {
  return (pt.GetX() >= m_pMin.GetX() && pt.GetX() <= m_pMax.GetX() &&
	pt.GetY() >= m_pMin.GetY() && pt.GetY() <= m_pMax.GetY() &&
	pt.GetZ() >= m_pMin.GetZ() && pt.GetZ() <= m_pMax.GetZ());
}

cannoli::AABB cannoli::AABB::Expand(cannoli::Vec3f &pt) {
  return AABB(PointXYZ(std::min(m_pMin.GetX(), pt.GetX()),
					   std::min(m_pMin.GetY(), pt.GetY()),
					   std::min(m_pMin.GetZ(), pt.GetZ())),
			  PointXYZ(std::max(m_pMax.GetX(), pt.GetX()),
					   std::max(m_pMax.GetY(), pt.GetY()),
					   std::max(m_pMax.GetZ(), pt.GetZ())));
}
