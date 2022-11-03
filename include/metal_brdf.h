#ifndef CANNOLI_SRC_METAL_BRDF_H_
#define CANNOLI_SRC_METAL_BRDF_H_

#include "material.h"

namespace cannoli {
class MetalBRDF : public Material {
 public:
  MetalBRDF(ColorRGB a, float fuzz) : m_albedo(a), m_fuzz(fuzz) {}

  [[nodiscard]] ColorRGB GetAlbedo() const override {
	return m_albedo;
  }

  LightRay Scatter(const LightRay &ray_in, const PointXYZ &hit_point, const Vec3f &surf_normal) override;

 private:
  ColorRGB m_albedo;
  float m_fuzz;
};

} // namespace cannoli

#endif //CANNOLI_SRC_METAL_BRDF_H_
