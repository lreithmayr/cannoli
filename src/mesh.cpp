#include "mesh.h"

cannoli::Mesh::Mesh(objl::Mesh &mesh, std::shared_ptr<Material> &material) :
  m_indices(mesh.Indices),
  m_name(mesh.MeshName),
  m_meshMaterial(material),
  m_faceCount(m_indices.size() / 3) {

  // Convert the vertex positions from objl's Vector3 format to Vec3f
  for (const auto &objl_vertex : mesh.Vertices) {
	m_vertices.push_back(cannoli::vec3ToVec3f(objl_vertex.Position));
  }


  // Compute the mesh's axis-alignes bounding box (AABB)
  computeAABB();
  fmt::print("Constructed Mesh {} \n Number of Vertices: {} \n Number of Faces: {} \n", m_name, m_vertices.size(), m_faceCount);
}

bool cannoli::Mesh::computeTriangleIntersection(LightRay &ray,
												const float &t_min,
												const float &t_max,
												HitRecord &hit_record,
												int triangle_nr) {

  // Get triangle vertices from mesh
  cannoli::Vec3f v0 = m_vertices[m_indices[triangle_nr * 3]];
  cannoli::Vec3f v1 = m_vertices[m_indices[triangle_nr * 3 + 1]];
  cannoli::Vec3f v2 = m_vertices[m_indices[triangle_nr * 3 + 2]];

  // Transform the coordinates of the vertices to the CS of the ray
  // 1) Translate vertices based on the ray origin
  cannoli::PointXYZ v0t = v0 - ray.getOrigin();
  cannoli::PointXYZ v1t = v1 - ray.getOrigin();
  cannoli::PointXYZ v2t = v2 - ray.getOrigin();

  // 2) permute the components such that the z-dimension is the one where the absolute value of the ray's direction
  // is largest
  cannoli::Vec3f ray_dir_permuted = ray.permuteDirection();
  std::array<int, 3> k_vals = ray.getKVals();

  v0t = permute(v0t, k_vals.at(0), k_vals.at(1), k_vals.at(2));
  v1t = permute(v1t, k_vals.at(0), k_vals.at(1), k_vals.at(2));
  v2t = permute(v2t, k_vals.at(0), k_vals.at(1), k_vals.at(2));

  // 3) Shear transformation to align the ray direction with the +z axis (for now only for x and y coordinates)
  float ray_dir_permuted_z = ray_dir_permuted.getZ();
  float s_x = -ray_dir_permuted.getX() / ray_dir_permuted_z;
  float s_y = -ray_dir_permuted.getY() / ray_dir_permuted_z;
  float s_z = 1.f / ray_dir_permuted_z;

  float v0t_x = v0t.getX();
  float v0t_y = v0t.getY();
  float v1t_x = v1t.getX();
  float v1t_y = v1t.getY();
  float v2t_x = v2t.getX();
  float v2t_y = v2t.getY();

  v0t_x += s_x * v0t.getZ();
  v0t_y += s_y * v0t.getZ();
  v1t_x += s_x * v1t.getZ();
  v1t_y += s_y * v1t.getZ();
  v2t_x += s_x * v2t.getZ();
  v2t_y += s_y * v2t.getZ();

  // 4) Compute edge function coefficients
  float e0 = v1t_x * v2t_y - v1t_y * v2t_x;
  float e1 = v2t_x * v0t_y - v2t_y * v0t_x;
  float e2 = v0t_x * v1t_y - v0t_y * v1t_x;

  if ((e0 < 0 || e1 < 0 || e2 < 0) && (e0 > 0 || e1 > 0 || e2 > 0)) {
	return false;
  }

  float det = e0 + e1 + e2;
  if (det == 0.f) {
	return false;
  }

  float v0t_sz = v0t.getZ() * s_z;
  float v1t_sz = v1t.getZ() * s_z;
  float v2t_sz = v2t.getZ() * s_z;

  float t_scaled = e0 * v0t_sz + e1 * v1t_sz + e2 * v2t_sz;

  if ((det < 0 && (t_scaled >= 0 || t_scaled < t_max * det))
	|| (det > 0 && (t_scaled <= 0 || t_scaled > t_max * det))) {
	return false;
  }

  float invDet = 1 / det;
  float u = e0 * invDet;
  float v = e1 * invDet;
  float w = e2 * invDet;
  float t = t_scaled * invDet;

  Vec3f v1_v0 = v1 - v0;
  Vec3f v2_v0 = v2 - v0;
  Vec3f normal = cross(v1_v0, v2_v0);

  hit_record.t = t;
  hit_record.hit_point = ray.getPosition(t);
  hit_record.u = u;
  hit_record.v = v;
  hit_record.surface_normal = normal;

  return true;
}

cannoli::LightRay cannoli::Mesh::computeSurfaceInteraction(
  const LightRay &ray,
  const HitRecord &hit_record) {
  return m_meshMaterial->scatter(ray, hit_record.hit_point, hit_record.surface_normal);
}

void cannoli::Mesh::computeAABB() {
  for (auto &pt : m_vertices) {
	if (!m_aabb.isInside(pt)) {
	  m_aabb = m_aabb.expand(pt);
	}
  }
}
