#include "lambertian_brdf.h"

cannoli::LightRay cannoli::LambertianBRDF::Scatter(const LightRay &ray_in,
                                                   const PointXYZ &hit_point,
                                                   const Vec3f &surf_normal) {
  Vec3f scatter_dir = surf_normal + cannoli::Vec3f::rand_within_unit_sphere();

  double eps = 1e-8;
  if (std::fabs(scatter_dir[0]) < eps && std::fabs(scatter_dir[0]) < eps && std::fabs(scatter_dir[0]) < eps) {
    scatter_dir = surf_normal;
  }

  cannoli::LightRay scattered_ray(hit_point, scatter_dir);
  return scattered_ray;
}