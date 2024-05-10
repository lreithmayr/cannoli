#include "aabb.h"

bool cannoli::AABB::computeAABBIntersection(const LightRay &ray, float t_min, float t_max) {
  for (int i = 0; i < 3; ++i) {
	float invRayDir = 1 / ray.getDirection()[i];
	float tNear = (m_pMin[i] - ray.getOrigin()[i]) * invRayDir;
	float tFar = (m_pMax[i] - ray.getOrigin()[i]) * invRayDir;
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

bool cannoli::AABB::isInside(PointXYZ &pt) {
  return (pt.getX() >= m_pMin.getX() && pt.getX() <= m_pMax.getX() &&
	pt.getY() >= m_pMin.getY() && pt.getY() <= m_pMax.getY() &&
	pt.getZ() >= m_pMin.getZ() && pt.getZ() <= m_pMax.getZ());
}

cannoli::AABB cannoli::AABB::expand(Vec3f &pt) {
  return AABB(PointXYZ(std::min(m_pMin.getX(), pt.getX()),
					   std::min(m_pMin.getY(), pt.getY()),
					   std::min(m_pMin.getZ(), pt.getZ())),
			  PointXYZ(std::max(m_pMax.getX(), pt.getX()),
					   std::max(m_pMax.getY(), pt.getY()),
					   std::max(m_pMax.getZ(), pt.getZ())));
}
