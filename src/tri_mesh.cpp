#include "tri_mesh.h"

bool cannoli::TriMesh::Hit(
  const cannoli::LightRay &ray, const float &t_min, const float &t_max, cannoli::HitRecord
&hit_record)
{
  return true;
}

cannoli::LightRay cannoli::TriMesh::ComputeSurfaceInteraction(const LightRay &ray, HitRecord &hit_record)
{
  return m_material->Scatter(ray, hit_record.hit_point, hit_record.surface_normal);
}
