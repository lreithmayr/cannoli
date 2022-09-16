#include "sphere.h"

bool cannoli::Sphere::Hit(const LightRay &ray, const float &t_min, const float &t_max, HitRecord &hit_record) {
  Vec3f dist_origin_center = ray.GetOrigin() - m_center; // (A - C)
  double a_2 = ray.GetDirection().length_squared();
  double half_a1 = dot(dist_origin_center, ray.GetDirection());
  double a_0 = dist_origin_center.length_squared() - (m_radius * m_radius);
  double discriminant = half_a1 * half_a1 - a_2 * a_0;
  double sqrt_discriminant = std::sqrt(discriminant);

  if (discriminant < 0)
	return false;

  auto root = (-half_a1 - sqrt_discriminant) / a_2;
  if (root < t_min || t_max < root) {
	root = (-half_a1 + sqrt_discriminant) / a_2;
	if (root < t_min || t_max < root) {
	  return false;
	}
  }

  hit_record.t = root;
  hit_record.hit_point = ray.Position(root);
  hit_record.surface_normal = CalculateSurfaceNormal(ray, hit_record.t, hit_record);

  return true;
}

cannoli::Vec3f cannoli::Sphere::CalculateSurfaceNormal(const cannoli::LightRay &ray, float t, HitRecord &hit_record) {
  Vec3f outward_normal = ((ray.Position(t) - m_center) * (1 / m_radius));
  if (dot(ray.GetDirection(), outward_normal) < 0) {
	hit_record.front_face = true;
	return outward_normal.normalize();
  } else {
	hit_record.front_face = false;
	return -outward_normal.normalize();
  }
}

cannoli::LightRay cannoli::Sphere::ComputeSurfaceInteraction(const LightRay &ray, HitRecord &hit_record) {
  return m_material->Scatter(ray, hit_record.hit_point, hit_record.surface_normal);
}
