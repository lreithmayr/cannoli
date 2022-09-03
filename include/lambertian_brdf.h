#ifndef CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_
#define CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_

#include "material.h"

namespace cannoli {
  class LambertianBRDF : public Material {
   public:
	LambertianBRDF() = default;

	Vec3f Scatter(PointXYZ &hit_point, Vec3f &surf_normal) override;
  };
} // namespace cannoli

#endif //CANNOLI_INCLUDE_LAMBERTIAN_BRDF_H_
