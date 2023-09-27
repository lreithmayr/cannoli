#ifndef CANNOLI_INCLUDE_MATERIAL_H_
#define CANNOLI_INCLUDE_MATERIAL_H_

#include "point.h"
#include "light_ray.h"
#include "color.h"

namespace cannoli {
class Material {
 public:
  Material() = default;
  virtual ~Material() = default;

  [[nodiscard]] virtual ColorRGB GetAlbedo() const {
    return m_albedo;
  }

  virtual LightRay Scatter(const LightRay &ray_in, const PointXYZ &hit_point, const Vec3f &surf_normal) = 0;

 protected:
  ColorRGB m_albedo;
};
} // namespace cannoli
#endif //CANNOLI_INCLUDE_MATERIAL_H_
