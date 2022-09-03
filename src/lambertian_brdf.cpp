#include "lambertian_brdf.h"

cannoli::Vec3f cannoli::LambertianBRDF::Scatter(cannoli::PointXYZ &hit_point, cannoli::Vec3f &surf_normal) {
  return hit_point + surf_normal + cannoli::Vec3f::rand_within_unit_sphere();
}