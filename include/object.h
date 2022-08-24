#ifndef CANNOLI_INCLUDE_OBJECT_H_
#define CANNOLI_INCLUDE_OBJECT_H_

#include "vec3f.h"
#include "light_ray.h"
#include "material.h"
#include "object_type.h"

namespace cannoli {
  class Object {
   public:
	Object() = default;

	OBJECT_TYPE GetType() {
	  return m_type;
	}

	virtual bool Hit(const LightRay& ray) = 0;

   protected:
	OBJECT_TYPE m_type{DEFAULT};
	Material m_material;
  };
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_OBJECT_H_
