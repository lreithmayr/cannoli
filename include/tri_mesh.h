#ifndef CANNOLI_SRC_MESH_H_
#define CANNOLI_SRC_MESH_H_

#include "object.h"

#include <string>

#include "pmp/SurfaceMesh.h"
#include "pmp/io/io.h"

namespace cannoli {
class TriMesh : public Object {
 public:
  explicit TriMesh(std::string &mesh_path)
  {
	pmp::read(m_mesh, mesh_path);
  }

  [[nodiscard]] int GetFaces() const
  {
	return m_mesh.n_faces();
  }

  bool Hit(const LightRay &ray, const float &t_min, const float &t_max, HitRecord &hit_record) override;

  cannoli::LightRay ComputeSurfaceInteraction(const LightRay &ray, HitRecord &hit_record) override;

 protected:
  pmp::SurfaceMesh m_mesh{};
};
} // namespace cannoli
#endif //CANNOLI_SRC_MESH_H_
