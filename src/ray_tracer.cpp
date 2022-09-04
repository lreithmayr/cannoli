#include "ray_tracer.h"

void cannoli::RayTracer::Trace() {
  // 1. Calculate ray from POV to a pixel
  // 2. Determine which objects the ray intersects
  // 3. Compute a color/material etc. for that intersection point

  std::ofstream ppm_image;
  ppm_image.open(m_outFile);
  ppm_image << "P3\n" << m_canvas.width << ' ' << m_canvas.height << "\n255\n";

  const auto samples = 50;
  int max_bounces = 50;

  for (int i = m_canvas.height - 1; i >= 0; i--) {
	auto prog = (static_cast<float>(i) / static_cast<float>(m_canvas.height));
	cannoli::ProgressBar(1 - prog);

	for (int j = 0; j < m_canvas.width; j++) {
	  m_pixelColor.SetXYZ(0, 0, 0);
	  for (int s = 0; s < samples; s++) {
		auto u = (j + random_float()) / (m_canvas.width - 1);
		auto v = (i + random_float()) / (m_canvas.height - 1);
		Vec3f dir = m_camera.GetViewportLLC() + m_camera.GetHorizontal() * u + m_camera.GetVertical() * v
			- m_camera.GetOrigin();

		LightRay ray(m_camera.GetOrigin(), dir);
		m_pixelColor += ComputeColor(ray, max_bounces);
	  }
	  WritePPMImage(ppm_image, samples);
	}
  }
  ppm_image.close();
}

cannoli::ColorRGB cannoli::RayTracer::ComputeColor(const cannoli::LightRay &ray, int n_bounces) {
  HitRecord hit_record;
  float eps = 0.001;

  if (n_bounces <= 0)
	return ColorRGB(0, 0, 0);

  for (Object *object : m_scene.GetObjectList()) {
	if (object->Hit(ray, eps, infinity, hit_record)) {
	  LightRay scattered_ray = object->ComputeSurfaceInteraction(ray, hit_record);
	  float albedo = object->GetMaterial()->GetReflectionIntensity();
	  return albedo * ComputeColor(scattered_ray, n_bounces - 1);
	}
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

  stream << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		 << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		 << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
