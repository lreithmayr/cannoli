#include "mesh.h"

cannoli::Mesh::Mesh(const std::string &obj_fpath, const std::shared_ptr<Material> &material) {
  objl::Loader loader;
  bool loadout = loader.LoadFile(obj_fpath);
  if (loadout) {
	cannoli::LOG("Mesh loaded successfully.");

	objl::Mesh mesh = loader.LoadedMeshes[0];
	m_name = mesh.MeshName;
	m_vertices = mesh.Vertices;
	m_indices = mesh.Indices;
	m_meshMaterial = material;
	m_faceCount = m_indices.size() / 3;

	ConstructTriangles();
  } else {
	cannoli::ERROR("Mesh failed to load!");
  }
}

void cannoli::Mesh::ConstructTriangles() {


  for (int i = 0; i < m_faceCount; ++i) {
	// Get triangle vertices from mesh and convert them to Vec3f's
	objl::Vector3 v0_objl = m_vertices[m_indices[i * 3]].Position;
	objl::Vector3 v1_objl = m_vertices[m_indices[i * 3 + 1]].Position;
	objl::Vector3 v2_objl = m_vertices[m_indices[i * 3 + 2]].Position;

	Vec3f v0 = Vector3ToVec3f(v0_objl);
	Vec3f v1 = Vector3ToVec3f(v1_objl);
	Vec3f v2 = Vector3ToVec3f(v2_objl);

	cannoli::Triangle tri(v0, v1, v2);

	m_triangles.push_back(tri);
  }
}