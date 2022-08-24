#ifndef CANNOLI_INCLUDE_SCENE_H_
#define CANNOLI_INCLUDE_SCENE_H_

#include "object.h"
#include <vector>

namespace cannoli {
  class Scene {
   public:
	Scene() = default;

	void Add(Object* const& object) {
	  mp_sceneObjects.emplace_back(object);
	}

	[[nodiscard]] std::vector<Object*> GetObjectList() const {
	  return mp_sceneObjects;
	};

   private:
	std::vector<Object*> mp_sceneObjects;
  };

} // namespace cannoli
#endif //CANNOLI_INCLUDE_SCENE_H_
