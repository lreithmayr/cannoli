#ifndef CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_
#define CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_

#include <cmath>
#include "material.h"
#include "light_ray.h"

namespace cannoli {
  class LambertianBRDF : public Material {
   public:
	LambertianBRDF() = default;

	[[nodiscard]] float GetReflectionIntensity() const override {
	  return m_lambertianReflectance;
	}

	LightRay Scatter(const LightRay &ray_in, PointXYZ &hit_point, Vec3f &surf_normal) override;

   private:
	float m_lambertianReflectance = 0.0;
  };
} // namespace cannoli

#endif //CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_
