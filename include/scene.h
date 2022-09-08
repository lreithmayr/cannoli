#ifndef CANNOLI_INCLUDE_SCENE_H_
#define CANNOLI_INCLUDE_SCENE_H_

#include "object.h"
#include <vector>

namespace cannoli {
  class Scene {
   public:
	Scene() = default;

	void Add(std::shared_ptr<Object> &object) {
	  m_sceneObjects.emplace_back(object);
	}

	[[nodiscard]] std::vector<std::shared_ptr<Object>> GetObjectList() const {
	  return m_sceneObjects;
	};

   private:
	std::vector<std::shared_ptr<Object>> m_sceneObjects{};
  };

} // namespace cannoli
#endif //CANNOLI_INCLUDE_SCENE_H_
