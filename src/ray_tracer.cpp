#include "ray_tracer.h"

void cannoli::RayTracer::Trace() {
  // 1. Calculate ray from POV to a pixel
  // 2. Determine which objects the ray intersects
  // 3. Compute a color/material etc. for that intersection point

  std::ofstream ppm_image;
  ppm_image.open(m_outFile);
  ppm_image << "P3\n" << m_canvas.width << ' ' << m_canvas.height << "\n255\n";

  ProcessScene();

  for (int i = m_canvas.height - 1; i >= 0; i--) {
	for (int j = 0; j < m_canvas.width; j++) {
	  // std::cerr << "\rScanlines remaining: " << i << '\n';

	  auto v = static_cast<float>(i) / (m_canvas.height - 1);
	  auto u = static_cast<float>(j) / (m_canvas.width - 1);
	  Vec3f dir =
		  m_camera.GetViewportLLC() + m_camera.GetHorizontal() * u + m_camera.GetVertical() * v - m_camera.GetOrigin();

	  LightRay ray(m_camera.GetOrigin(), dir);
	  // ComputeHit(ray);
	  ComputeRayColor(ray);

	  WritePPMImage(ppm_image, m_pixelColor);
	}
  }

  // std::cerr << "\n Done! \n";
  ppm_image.close();
}

void cannoli::RayTracer::Stop() {
  m_stopTrace = true;
}

void cannoli::RayTracer::ProcessScene() {
  for (auto object : m_scene.GetObjectList()) {
	if (object->GetType() == DEFAULT) {
	  std::cout << "DEFAULT" << "\n";
	} else if (object->GetType() == SPHERE) {
	  std::cout << "SPHERE" << "\n";
	}
  }
}

void cannoli::RayTracer::ComputeRayColor(cannoli::LightRay& ray) {
  cannoli::Vec3f unit_direction = ray.GetDirection().normalize();
  auto t = 0.5 * (unit_direction.GetY() + 1.0);
  m_pixelColor = (1.0 - t) * ColorRGB(1.0, 1.0, 1.0) + t * ColorRGB(0.5, 0.7, 1.0);
}