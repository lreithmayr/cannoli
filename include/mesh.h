#ifndef CANNOLI_SRC_MESH_H_
#define CANNOLI_SRC_MESH_H_

#include "obj_file_loader.h"
#include "utils.h"
#include "light_ray.h"
#include "hit_record.h"
#include "vec3f.h"
#include "material.h"
#include "object.h"
#include "aabb.h"
#include "bvh.h"

#include <string>
#include <memory>

namespace cannoli {
class Mesh {
 public:
  explicit Mesh(objl::Mesh &mesh, std::shared_ptr<Material> &material);

  [[nodiscard]] std::vector<Vec3f> getVertices() const {
	return m_vertices;
  }

  [[nodiscard]] std::vector<uint> getIndices() const {
	return m_indices;
  }

  [[nodiscard]] int getFaceCount() const {
	return m_triangleCount;
  }

  [[nodiscard]] std::shared_ptr<Material> getMaterial() const {
	return m_meshMaterial;
  }

  [[nodiscard]] std::shared_ptr<AABB> getAABB() const {
	return std::make_shared<AABB>(m_aabb);
  }

  [[nodiscard]] std::shared_ptr<BVH> getBBVH() const {
	return std::make_shared<BVH>(m_bvh);
  }

  bool computeTriangleIntersection(
	LightRay &ray,
	const float &t_min,
	const float &t_max,
	HitRecord &hit_record,
	int triangle_nr);
  LightRay computeSurfaceInteraction(const LightRay &ray, const HitRecord &hit_record);
  void computeAABB();
  void constructBVH();

 private:
  std::vector<cannoli::Vec3f> m_vertices;
  std::vector<uint> m_indices;
  std::string m_name;
  std::shared_ptr<Material> m_meshMaterial;

 private:
  int m_triangleCount = 0;
  AABB m_aabb;
  BVH m_bvh;
};
} // namespace cannoli
#endif //CANNOLI_SRC_MESH_H_
