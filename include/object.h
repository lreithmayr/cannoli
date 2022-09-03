#ifndef CANNOLI_INCLUDE_OBJECT_H_
#define CANNOLI_INCLUDE_OBJECT_H_

#include "vec3f.h"
#include "light_ray.h"
#include "material.h"
#include "object_type.h"
#include "hit_record.h"

namespace cannoli {

  class Object {
   public:
	Object() = default;

	void SetType(ObjectType type) {
	  m_type = type;
	}

	[[nodiscard]] ObjectType GetType() const {
	  return m_type;
	}
	virtual bool Hit(const LightRay &ray, float t_min, float t_max, HitRecord &hit_record) = 0;
	virtual cannoli::LightRay ComputeSurfaceInteraction(const LightRay &ray, HitRecord &hit_record) = 0;

   protected:
	ObjectType m_type{ObjectType::DEFAULT};
	Material *m_material = nullptr;
  };
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_OBJECT_H_
