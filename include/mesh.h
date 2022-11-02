#ifndef CANNOLI_SRC_MESH_H_
#define CANNOLI_SRC_MESH_H_

#include "obj_file_loader.h"
#include "utils.h"
#include "vec3f.h"
#include "material.h"
#include "triangle.h"

#include <string>
#include <memory>
#include <vector>

namespace cannoli {
class Mesh {
 public:
  Mesh(const std::string &obj_fpath, const std::shared_ptr<Material> &material);

  [[nodiscard]] std::vector<objl::Vertex> GetVertices() const {
	return m_vertices;
  }

  [[nodiscard]] std::vector<uint> GetIndices() const {
	return m_indices;
  }

  [[nodiscard]] int GetFaceCount() const {
	return m_faceCount;
  }

  [[nodiscard]] std::shared_ptr<Material> GetMaterial() {
	return m_meshMaterial;
  }

  [[nodiscard]] std::shared_ptr<std::vector<Triangle>> GetTriangles() const {
	return std::make_shared<std::vector<Triangle>>(m_triangles);
  }

  void ConstructTriangles();

 private:
  std::vector<objl::Vertex> m_vertices;
  std::vector<uint> m_indices;
  std::string m_name;
  std::shared_ptr<Material> m_meshMaterial;
  std::vector<Triangle> m_triangles;

 private:
  int m_faceCount = 0;
};
} // namespace cannoli
#endif //CANNOLI_SRC_MESH_H_
