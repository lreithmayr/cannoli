#include "ray_tracer.h"

void cannoli::RayTracer::Trace() {
  HitRecord hit_record;
  auto mesh = m_scene.GetMeshesInScene();
  std::vector<Triangle> triangles_in_mesh = *mesh[0]->GetTriangles();

  for (int i = m_canvas.height - 1; i >= 0; --i) {
	cannoli::ProgressBar(1 - (static_cast<float>(i) / static_cast<float>(m_canvas.height)));

	for (int j = 0; j < m_canvas.width; ++j) {
	  ResetPixel();

	  for (int s = 0; s < m_samples; ++s) {
		LightRay ray = EmitRay(j, i);
		m_pixelColor += ComputeColor(ray, m_maxBounces, hit_record, infinity, triangles_in_mesh);
	  }

	  WritePPMImage(m_ppmImage, m_samples);
	}
  }
  m_ppmImage.close();
}

void cannoli::RayTracer::SetUp() {
  m_ppmImage.open(m_outFile);
  m_ppmImage << "P3\n" << m_canvas.width << ' ' << m_canvas.height << "\n255\n";
}

void cannoli::RayTracer::ResetPixel() {
  m_pixelColor.SetXYZ(0, 0, 0);
}

cannoli::LightRay cannoli::RayTracer::EmitRay(int pixel_x, int pixel_y) {
  auto u = (pixel_x + random_float()) / (m_canvas.width - 1);
  auto v = (pixel_y + random_float()) / (m_canvas.height - 1);
  Vec3f dir = m_camera.GetViewportLLC() + m_camera.GetHorizontal() * u + m_camera.GetVertical() * v
	- m_camera.GetOrigin();
  cannoli::LightRay ray(m_camera.GetOrigin(), dir);
  return ray;
}

cannoli::ColorRGB cannoli::RayTracer::ComputeColor(const cannoli::LightRay &ray,
												   int n_bounces,
												   HitRecord &hit_record,
												   float t_max,
												   std::vector<Triangle> &triangles) {
  HitRecord temp_hit_record;
  float closest_so_far = t_max;
  float eps = 0.001;
  Triangle closest_triangle;
  bool hit_triangle = false;

  if (n_bounces <= 0) {
	return ColorRGB(0, 0, 0);
  }

  // Iterate through all triangles in the mesh and check for a hit
  for (auto &triangle : triangles) {
	if (triangle.Hit(ray, eps, closest_so_far, temp_hit_record)) {
	  closest_so_far = temp_hit_record.t;
	  hit_record = temp_hit_record;
	  closest_triangle = triangle;
	  hit_triangle = true;
	}
  }

  // Have the ray interact with the triangle
  if (hit_triangle) {
	LightRay scattered_ray = closest_triangle.ComputeSurfaceInteraction(ray, hit_record);
	ColorRGB albedo = closest_triangle.GetMaterial()->GetAlbedo();
	return albedo * ComputeColor(scattered_ray, n_bounces - 1, hit_record, closest_so_far, triangles);
  }

  // In case of no hit, return a uniform background color
  cannoli::Vec3f unit_direction = ray.GetDirection().normalize();
  float t = 0.5 * (unit_direction.GetY() + 1.0);
  return (1.0 - t) * ColorRGB(1.0, 1.0, 1.0) + t * ColorRGB(0.5, 0.7, 1.0);
}

void cannoli::RayTracer::WritePPMImage(std::ofstream &stream, int samples) {
  float r = m_pixelColor.GetX();
  float g = m_pixelColor.GetY();
  float b = m_pixelColor.GetZ();

  auto scale = 1.0 / samples;

  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  stream << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		 << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

