#include "metal_brdf.h"

cannoli::LightRay cannoli::MetalBRDF::scatter(const LightRay &ray_in,
											  const PointXYZ &hit_point,
											  const Vec3f &surf_normal) {
  // Direction of the reflected ray can be computed using the direction of the incoming ray l and the surface normal
  Vec3f l = ray_in.getDirection().normalize();
  Vec3f reflection_dir = l - 2 * dot(l, surf_normal) * surf_normal;
  LightRay reflected_ray(hit_point, reflection_dir + m_fuzz * Vec3f::computeRandWithinUnitSphere());
  return reflected_ray;
}
