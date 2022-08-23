#include "ray_tracer.h"

void cannoli::RayTracer::Trace() {
  std::ofstream ppm_image;
  ppm_image.open(m_outFile);
  ppm_image << "P3\n" << m_img.width << ' ' << m_img.height << "\n255\n";

  for (int i = m_img.height - 1; i >= 0; i--) {
	for (int j = 0; j < m_img.width; j++) {
	  std::cerr << "\rScanlines remaining: " << i << '\n';

	  auto v = float(i) / (m_img.height - 1);
	  auto u = float(j) / (m_img.width - 1);
	  Vec3f dir = m_camera.GetViewportLLC() + m_camera.GetHorizontal() * u + m_camera.GetVertical() * v - m_camera.GetOrigin();

	  CastRay(dir);

	  WritePPMImage(ppm_image, m_pixelColor);
	}
  }

  std::cerr << "\n Done! \n";
  ppm_image.close();
}

void cannoli::RayTracer::Stop() {
  m_stopTrace = true;
}

void cannoli::RayTracer::CastRay(const cannoli::Vec3f& dir) {
  // 1. Calculate ray from POV to a pixel
  // 2. Determine which objects the ray intersects
  // 3. Compute a color/material etc. for that intersection point

  LightRay ray(m_camera.GetOrigin(), dir);
  ComputeRayColor(ray);
}

 void cannoli::RayTracer::ComputeRayColor(cannoli::LightRay& ray) {
  cannoli::Vec3f unit_direction = ray.GetDirection().normalize();
  auto t = 0.5 * (unit_direction.GetY() + 1.0);
  m_pixelColor = (1.0 - t) * ColorRGB(1.0, 1.0, 1.0) + t * ColorRGB(0.5, 0.7, 1.0);
}