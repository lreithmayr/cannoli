#ifndef CANNOLI_SRC_METAL_BRDF_H_
#define CANNOLI_SRC_METAL_BRDF_H_

#include "material.h"

namespace cannoli {
  class MetalBRDF : public Material {
   public:
	explicit MetalBRDF(ColorRGB a) : m_albedo(a) {}

	[[nodiscard]] ColorRGB GetAlbedo() const override {
	  return m_albedo;
	}

	LightRay Scatter(const LightRay &ray_in, const PointXYZ &hit_point, const Vec3f &surf_normal) override;

   private:
	ColorRGB m_albedo;
  };

} // namespace cannoli

#endif //CANNOLI_SRC_METAL_BRDF_H_
