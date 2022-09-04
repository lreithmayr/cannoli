#include "lambertian_brdf.h"

cannoli::LightRay cannoli::LambertianBRDF::Scatter(const LightRay &ray_in, const PointXYZ &hit_point, const Vec3f &surf_normal) {
  Vec3f inverse_ray_dir = -ray_in.GetDirection();

  // L: Normalized light direction vector pointing from the hit point (at the surface) towards the light direction
  Vec3f L = (hit_point + inverse_ray_dir).normalize();
  float I = fabsf(dot(L, surf_normal));
  m_lambertianAlbedo.SetXYZ(I, I, I);

  Vec3f scatter_dir = surf_normal + cannoli::Vec3f::rand_within_unit_sphere();
  cannoli::LightRay scattered_ray(hit_point, scatter_dir);
  return scattered_ray;
}