#ifndef CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_
#define CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_

#include <cmath>
#include "material.h"
#include "light_ray.h"

namespace cannoli {
class LambertianBRDF : public Material {
 public:
  LambertianBRDF() = default;
  explicit LambertianBRDF(ColorRGB &albedo) : m_lambertianAlbedo(albedo) {}
  ~LambertianBRDF() = default;

  [[nodiscard]] ColorRGB GetAlbedo() const override
  {
	return m_lambertianAlbedo;
  }

  LightRay Scatter(const LightRay &ray_in, const PointXYZ &hit_point, const Vec3f &surf_normal) override;

 private:
  ColorRGB m_lambertianAlbedo;
};
} // namespace cannoli

#endif //CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_
