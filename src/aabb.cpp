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
