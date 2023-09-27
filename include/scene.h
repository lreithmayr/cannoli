#ifndef CANNOLI_INCLUDE_SCENE_H_
#define CANNOLI_INCLUDE_SCENE_H_

#include "mesh.h"

#include <vector>
#include <memory>

namespace cannoli {
class Scene {
 public:
  Scene() = default;

  void Add(const std::shared_ptr<Mesh> &mesh) {
    m_meshesInScene.emplace_back(mesh);
  }

  [[nodiscard]] std::vector<std::shared_ptr<Mesh>> GetMeshesInScene() const {
    return m_meshesInScene;
  };

 private:
  std::vector<std::shared_ptr<Mesh>> m_meshesInScene{};
};

} // namespace cannoli
#endif //CANNOLI_INCLUDE_SCENE_H_
