#ifndef CANNOLI_INCLUDE_LIGHT_RAY_H_
#define CANNOLI_INCLUDE_LIGHT_RAY_H_

#include "vec3f.h"
#include "point.h"

namespace cannoli {
  class LightRay {
   public:
	LightRay() = default;
	~LightRay() = default;

	[[nodiscard]] PointXYZ Position(float t) const {
	  return (m_origin + m_dir * t);
	}

   protected:
	PointXYZ m_origin{};
	Vec3f m_dir{};

  };
}

#endif //CANNOLI_INCLUDE_LIGHT_RAY_H_
