#include "ray_tracer.h"

void cannoli::RayTracer::Trace() {
  SetupImage();

  HitRecord hit_record;
  auto meshes_in_scene = m_scene.GetMeshesInScene();

  for (int y = m_canvas.height - 1; y >= 0; --y) {
	cannoli::ProgressBar(1 - (static_cast<float>(y) / static_cast<float>(m_canvas.height)));

	for (int x = 0; x < m_canvas.width; ++x) {
	  ResetPixel();

	  for (int s = 0; s < m_samples; ++s) {
		Vec3f dir = GenerateDirection(x, y);
		LightRay ray = EmitRay(m_camera.GetOrigin(), dir);
		m_pixelColor += ComputeColor(ray, m_maxBounces, hit_record, infinity, meshes_in_scene);
	  }

	  WritePPMImage(m_ppmImage, m_samples);
	}
  }

  m_ppmImage.close();
}

cannoli::ColorRGB cannoli::RayTracer::ComputeColor(cannoli::LightRay &ray,
												   int n_bounces,
												   HitRecord &hit_record,
												   float t_max,
												   std::vector<std::shared_ptr<Mesh>> &meshes_in_scene) {
  HitRecord temp_hit_record;
  float closest_so_far = t_max;
  float eps = 0.001;
  std::shared_ptr<Mesh> closest_mesh = nullptr;
  bool hit_triangle = false;

  if (n_bounces <= 0) {
	return ColorRGB(0, 0, 0);
  }

  for (auto &mesh : meshes_in_scene) {
	for (int i = 0; i < mesh->GetFaceCount(); ++i) {
	  if (mesh->RayTriangleIntersect(ray, eps, closest_so_far, temp_hit_record, i)) {
		closest_so_far = temp_hit_record.t;
		hit_record = temp_hit_record;
		closest_mesh = mesh;
		hit_triangle = true;
	  }
	}
  }

  if (hit_triangle) {
	LightRay scattered_ray = closest_mesh->ComputeSurfaceInteraction(ray, hit_record);
	ColorRGB albedo = closest_mesh->GetMaterial()->GetAlbedo();
	return albedo * ComputeColor(scattered_ray, n_bounces - 1, hit_record, closest_so_far, meshes_in_scene);
  }

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

void cannoli::RayTracer::SetupImage() {
  m_ppmImage.open(m_outFile);
  m_ppmImage << "P3\n" << m_canvas.width << ' ' << m_canvas.height << "\n255\n";
}

void cannoli::RayTracer::ResetPixel() {
  m_pixelColor.SetXYZ(0, 0, 0);
}

cannoli::LightRay cannoli::RayTracer::EmitRay(const cannoli::Vec3f &origin, const cannoli::Vec3f &direction) {
  return cannoli::LightRay(origin, direction);
}

cannoli::Vec3f cannoli::RayTracer::GenerateDirection(const int pixel_x, const int pixel_y) {
  auto u = (pixel_x + random_float()) / (m_canvas.width - 1);
  auto v = (pixel_y + random_float()) / (m_canvas.height - 1);
  Vec3f
	dir = m_camera.GetViewportLLC() + m_camera.GetHorizontal() * u + m_camera.GetVertical() * v - m_camera.GetOrigin();
  return dir;
}

