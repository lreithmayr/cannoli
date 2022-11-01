#include "triangle.h"

bool cannoli::Triangle::Hit(const cannoli::LightRay &ray,
							const float &t_min,
							const float &t_max,
							cannoli::HitRecord &hit_record) {

// Transform the coordinates of the vertices to the CS of the ray
// 1) Translate vertices based on the ray origin
  cannoli::PointXYZ v0t = m_v0 - ray.GetOrigin();
  cannoli::PointXYZ v1t = m_v1 - ray.GetOrigin();
  cannoli::PointXYZ v2t = m_v2 - ray.GetOrigin();

// TODO: Store kx, ky, kz and s_x, s_y, s_z inside the LightRay class (these values are independent of the triangle
//  vertices and don't really need to be computed for each intersection test

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

  if ((det < 0 && (t_scaled >= 0 || t_scaled < t_max * det))
	|| (det > 0 && (t_scaled <= 0 || t_scaled > t_max * det))) {
	return false;
  }

  float invDet = 1 / det;
  float u = e0 * invDet;
  float v = e1 * invDet;
  float w = e2 * invDet;
  float t = t_scaled * invDet;

  hit_record.t = t;
  hit_record.hit_point = ray.Position(t);
  hit_record.u = u;
  hit_record.v = v;

  Vec3f v1_v0 = m_v1 - m_v0;
  Vec3f v2_v0 = m_v2 - m_v0;
  hit_record.surface_normal = cross(v1_v0, v2_v0);

  return true;
}

cannoli::LightRay cannoli::Triangle::ComputeSurfaceInteraction(const cannoli::LightRay &ray,
															   cannoli::HitRecord &hit_record) {
  return m_material->Scatter(ray, hit_record.hit_point, hit_record.surface_normal);
}