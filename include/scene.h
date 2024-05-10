#ifndef CANNOLI_INCLUDE_SCENE_H_
#define CANNOLI_INCLUDE_SCENE_H_

#include "mesh.h"
#include "metal_brdf.h"

#include <vector>
#include <memory>

namespace cannoli {
class Scene {
 public:
  Scene() = default;

  void load(std::string &path) {
	// Load all meshes from the .obj file
	objl::Loader loader;
	bool loadout = loader.LoadFile(path);
	if (loadout) {
	  for (auto &msh : loader.LoadedMeshes) {
		float rand = cannoli::random_float(0.1, 1.0);
		auto random_color = cannoli::ColorRGB::random(0.2, 0.9);
		auto random_fuzz = cannoli::random_float(0.2, 0.9);

		if (rand > 0.5) {
		  std::shared_ptr<cannoli::Material> mat = std::make_shared<cannoli::LambertianBRDF>(random_color);
		  cannoli::Mesh mesh(msh, mat);
		  addMesh(std::make_shared<cannoli::Mesh>(mesh));
		} else {
		  std::shared_ptr<cannoli::Material> mat = std::make_shared<cannoli::MetalBRDF>(random_color, random_fuzz);
		  cannoli::Mesh mesh(msh, mat);
		  addMesh(std::make_shared<cannoli::Mesh>(mesh));
		}

		fmt::print(" Random Color: {} \n", random_color);
		fmt::print(" Random Fuzz: {} \n", random_fuzz);
	  }

	} else {
	  fmt::print(stderr, "Failed to load mesh!\n");
	}
  };

  void addMesh(const std::shared_ptr<Mesh> &mesh) {
	m_meshesInScene.emplace_back(mesh);
  }

  [[nodiscard]] std::vector<std::shared_ptr<Mesh>> getMeshesInScene() const {
	return m_meshesInScene;
  };

 private:
  std::vector<std::shared_ptr<Mesh>> m_meshesInScene{};
};

} // namespace cannoli
#endif //CANNOLI_INCLUDE_SCENE_H_
