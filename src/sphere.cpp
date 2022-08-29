#include "sphere.h"

bool cannoli::Sphere::Hit(const LightRay& ray, const float t_min, const float t_max, HitRecord& hit_record) {
  Vec3f dist_origin_center = ray.GetOrigin() - m_center; // (A - C)
  auto a_2 = dot(ray.GetDirection(), ray.GetDirection());
  auto a_1 = 2 * dot(dist_origin_center, ray.GetDirection());
  auto a_0 = dot(dist_origin_center, dist_origin_center) - (m_radius * m_radius);

  auto discriminant = a_1 * a_1 - 4 * a_2 * a_0;
  if (discriminant < 0) return false;

  auto root = (-a_1 - sqrt(discriminant)) / (2 * a_2);
  if (root < t_min || root > t_max) {
	root = (-a_1 + sqrt(discriminant)) / (2 * a_2);
	if (root < t_min || root > t_max) {
	  return false;
	}
  }

  hit_record.t = root;
  hit_record.hit_point = ray.Position(root);
  hit_record.surface_normal = CalculateSurfaceNormal(ray, hit_record.t, hit_record).normalize();

  return true;
}

cannoli::Vec3f cannoli::Sphere::CalculateSurfaceNormal(const cannoli::LightRay& ray, float t, HitRecord& hit_record) {
  Vec3f outward_normal = ((ray.Position(t) - m_center) * (1 / m_radius));
  if (dot(ray.GetDirection(), outward_normal) < 0) {
	hit_record.front_face = true;
	return outward_normal;
  } else {
	hit_record.front_face = false;
	return -outward_normal;
  }
}
