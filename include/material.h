#ifndef CANNOLI_INCLUDE_MATERIAL_H_
#define CANNOLI_INCLUDE_MATERIAL_H_

#include "point.h"
#include "light_ray.h"

namespace cannoli {
  class Material {
   public:
	Material() = default;

	[[nodiscard]] virtual float GetReflectionIntensity() const {
	  return m_reflectionIntensity;
	}

	virtual LightRay Scatter(const LightRay &ray_in, PointXYZ &hit_point, Vec3f &surf_normal) = 0;

   protected:
	float m_reflectionIntensity = 0.0;
  };
} // namespace cannoli
#endif //CANNOLI_INCLUDE_MATERIAL_H_
