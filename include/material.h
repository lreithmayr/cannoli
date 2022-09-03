#ifndef CANNOLI_INCLUDE_MATERIAL_H_
#define CANNOLI_INCLUDE_MATERIAL_H_

#include "point.h"
#include "light_ray.h"

namespace cannoli {
  class Material {
   public:
	Material() = default;

	virtual LightRay Scatter(PointXYZ &hit_point, Vec3f &surf_normal) = 0;
  };
} // namespace cannoli
#endif //CANNOLI_INCLUDE_MATERIAL_H_
