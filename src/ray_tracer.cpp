#include "ray_tracer.h"

void cannoli::RayTracer::Trace() {
  // 1. Calculate ray from POV to a pixel
  // 2. Determine which objects the ray intersects
  // 3. Compute a color/material etc. for that intersection point

  std::ofstream ppm_image;
  ppm_image.open(m_outFile);
  ppm_image << "P3\n" << m_canvas.width << ' ' << m_canvas.height << "\n255\n";

  for (int i = m_canvas.height - 1; i >= 0; i--) {
	for (int j = 0; j < m_canvas.width; j++) {
	  auto v = static_cast<float>(i) / (m_canvas.height - 1);
	  auto u = static_cast<float>(j) / (m_canvas.width - 1);
	  Vec3f dir =
		  m_camera.GetViewportLLC() + m_camera.GetHorizontal() * u + m_camera.GetVertical() * v - m_camera.GetOrigin();

	  LightRay ray(m_camera.GetOrigin(), dir);

	  for (auto object : m_scene.GetObjectList()) {
		ComputeIntersections(ray, object);
	  }

	  WritePPMImage(ppm_image, m_pixelColor);
	}
  }
  ppm_image.close();
}

void cannoli::RayTracer::ComputeIntersections(const cannoli::LightRay& ray, cannoli::Object*& object) {
  HitRecord hit_record;
  if (object->Hit(ray, 0, infinity, hit_record)) {
	return m_pixelColor.SetXYZ(0.5 * (hit_record.surf_normal.GetX() + 1), 0.5 * (hit_record.surf_normal.GetY() + 1),
							   0.5 *
								   (hit_record.surf_normal
									   .GetZ()
									   + 1));
  }
  cannoli::Vec3f unit_direction = ray.GetDirection().normalize();
  hit_record.t = 0.5 * (unit_direction.GetY() + 1.0);
  m_pixelColor = (1.0 - hit_record.t) * ColorRGB(1.0, 1.0, 1.0) + hit_record.t * ColorRGB(0.5, 0.7, 1.0);
}

void cannoli::RayTracer::WritePPMImage(std::ofstream& stream, ColorRGB pixel_color) {
  stream << static_cast<int>(255.999 * pixel_color.GetX()) << ' '
		 << static_cast<int>(255.999 * pixel_color.GetY()) << ' '
		 << static_cast<int>(255.999 * pixel_color.GetZ()) << '\n';
}

void cannoli::RayTracer::Stop() {
  m_stopTrace = true;
}
