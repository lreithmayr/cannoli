#include "lambertian_brdf.h"
#include "light_ray.h"

cannoli::LightRay cannoli::LambertianBRDF::Scatter(cannoli::PointXYZ &hit_point, cannoli::Vec3f &surf_normal) {
  PointXYZ target = hit_point + surf_normal + cannoli::Vec3f::rand_within_unit_sphere();
  cannoli::LightRay scattered_ray(hit_point, target - hit_point);
  return scattered_ray;
}