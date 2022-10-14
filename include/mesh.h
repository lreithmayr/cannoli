#ifndef CANNOLI_SRC_MESH_H_
#define CANNOLI_SRC_MESH_H_

#include "obj_file_loader.h"
#include "utils.h"
#include "light_ray.h"
#include "hit_record.h"
#include "vec3f.h"

#include <string>

namespace cannoli {
class Mesh {
 public:
  explicit Mesh(std::string &obj_fpath);

  [[nodiscard]] std::vector<objl::Vertex> GetVertices() const {
	return m_vertices;
  }

  [[nodiscard]] std::vector<uint> GetIndices() const {
	return m_indices;
  }

  [[nodiscard]] int GetFaceCount() const {
	return m_faceCount;
  }

  bool RayTriangleIntersect(const cannoli::LightRay &ray,
							const float &t_min,
							const float &t_max,
							HitRecord &hit_record,
							int &triangle_nr);

 private:
  std::vector<objl::Vertex> m_vertices;
  std::vector<uint> m_indices;
  std::string m_name;
  objl::Material m_meshMaterial;

 private:
  int m_faceCount = 0;

};
} // namespace cannoli
#endif //CANNOLI_SRC_MESH_H_
