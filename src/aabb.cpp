#include "aabb.h"

bool cannoli::AABB::AABBIntersection(const LightRay &ray, float t_min, float t_max) {
  for (int i = 0; i < 3; ++i) {
	float invRayDir = 1 / ray.GetDirection()[i];
	float tNear = (m_pMin[i] - ray.GetOrigin()[i]) * invRayDir;
	float tFar = (m_pMax[i] - ray.GetOrigin()[i]) * invRayDir;
	if (tNear > tFar) {
	  std::swap(tNear, tFar);
	}

	t_min = tNear > t_min ? tNear : t_min;
	t_max = tFar < t_max ? tFar : t_max;
	if (t_min > t_max) {
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
