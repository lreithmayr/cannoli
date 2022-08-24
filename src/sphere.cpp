#include "sphere.h"

bool cannoli::Sphere::Hit(const cannoli::LightRay& ray) {
  Vec3f dist_origin_center = ray.GetOrigin() - m_center; // (A - C)
  auto a_2 = dot(ray.GetDirection(), ray.GetDirection());
  auto a_1 = 2 * dot(dist_origin_center, ray.GetDirection());
  auto a_0 = dot(dist_origin_center, dist_origin_center) - (m_radius * m_radius);

  auto discriminante = a_1 * a_1 - 4 * a_2 * a_0;

  return (discriminante > 0);
}
