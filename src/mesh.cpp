#include "mesh.h"

cannoli::Mesh::Mesh(std::string &obj_fvath) {
  objl::Loader loader;
  bool loadout = loader.LoadFile(obj_fvath);
  if (loadout) {
	cannoli::LOG("Mesh loaded successfully.");

	objl::Mesh mesh = loader.LoadedMeshes[0];
	m_name = mesh.MeshName;
	m_vertices = mesh.Vertices;
	m_indices = mesh.Indices;
	m_meshMaterial = mesh.MeshMaterial;

	m_faceCount = m_indices.size() / 3;
  } else {
	cannoli::LOG("Mesh failed to load!");
  }
}

bool cannoli::Mesh::RayTriangleIntersect(const cannoli::LightRay &ray,
										 const float &t_min,
										 const float &t_max,
										 cannoli::HitRecord &hit_record,
										 int &triangle_nr) {
  // Get triangle vertices from mesh
  objl::Vector3 v0 = m_vertices[m_indices[triangle_nr * 3]].Position;
  objl::Vector3 v1 = m_vertices[m_indices[triangle_nr * 3 + 1]].Position;
  objl::Vector3 v2 = m_vertices[m_indices[triangle_nr * 3 + 2]].Position;

  // Transform the coordinates of the vertices to the CS of the ray
  // 1) Translate vertices based on the ray origin
  cannoli::PointXYZ v0t = v0 - ray.GetOrigin();
  cannoli::PointXYZ v1t = v1 - ray.GetOrigin();
  cannoli::PointXYZ v2t = v2 - ray.GetOrigin();

  // TODO: Store kx, ky, kz and s_x, s_y, s_z inside the LightRay class (these values are indevendent of the triangle
  //  vertices and don't really need to be comvuted for each intersection test

  // 2) Permute the comvonents such that the z-dimension is the one where the absolute value of the ray's direction
  // is largest
  int kz = cannoli::MaxDimension(cannoli::Abs(ray.GetDirection()));
  int kx = kz + 1;
  if (kx == 3) {
	kx = 0;
  }
  int ky = kx + 1;
  if (ky == 3) {
	ky = 0;
  }
  cannoli::Vec3f ray_dir_permuted = cannoli::Permute(ray.GetDirection(), kx, ky, kz);
  v0t = Permute(v0t, kx, ky, kz);
  v1t = Permute(v1t, kx, ky, kz);
  v2t = Permute(v2t, kx, ky, kz);

  // 3) Shear transformation to align the ray direction with the +z axis (for now only for x and y coordinates)
  float ray_dir_permuted_z = ray_dir_permuted.GetZ();
  float s_x = -ray_dir_permuted.GetX() / ray_dir_permuted_z;
  float s_y = -ray_dir_permuted.GetY() / ray_dir_permuted_z;
  float s_z = 1.f / ray_dir_permuted_z;

  float v0t_x = v0t.GetX();
  float v0t_y = v0t.GetY();
  float v1t_x = v1t.GetX();
  float v1t_y = v1t.GetY();
  float v2t_x = v2t.GetX();
  float v2t_y = v2t.GetY();

  v0t_x += s_x * v0t.GetZ();
  v0t_y += s_y * v0t.GetZ();
  v1t_x += s_x * v1t.GetZ();
  v1t_y += s_y * v1t.GetZ();
  v2t_x += s_x * v2t.GetZ();
  v2t_y += s_y * v2t.GetZ();

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

  float v0t_sz = v0t.GetZ() * s_z;
  float v1t_sz = v1t.GetZ() * s_z;
  float v2t_sz = v2t.GetZ() * s_z;

  float t_scaled = e0 * v0t_sz + e1 * v1t_sz + e2 * v2t_sz;

  if (det < 0 && (t_scaled >= 0 || t_scaled < t_max * det)) {
	return false;
  } else if (det > 0 && (t_scaled <= 0 || t_scaled > t_max * det)) {
	return false;
  }

  float invDet = 1 / det;
  float u = e0 * invDet;
  float v = e1 * invDet;
  float w = e2 * invDet;
  float t = t_scaled * invDet;

  hit_record.t = t;
  hit_record.hit_point = ray.Position(t);

  return true;
}

