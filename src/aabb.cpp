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

bool cannoli::AABB::IsInside(cannoli::PointXYZ &p) {
  return (p.GetX() >= m_pMin.GetX() && p.GetX() <= m_pMax.GetX() &&
	p.GetY() >= m_pMin.GetY() && p.GetY() <= m_pMax.GetY() &&
	p.GetZ() >= m_pMin.GetZ() && p.GetZ() <= m_pMax.GetZ());
}

void cannoli::AABB::Expand(cannoli::Vec3f &pt_new) {
  if (pt_new.GetX() <= m_pMin.GetX() && pt_new.GetY() <= m_pMin.GetY() &&
	pt_new.GetZ() <= m_pMin.GetZ()) {
	m_pMin = pt_new;
  }

  if (pt_new.GetX() >= m_pMax.GetX() && pt_new.GetY() >= m_pMax.GetY() &&
	pt_new.GetZ() >= m_pMax.GetZ()) {
	m_pMax = pt_new;
  }
}
