#include "ray_tracer.h"

void cannoli::RayTracer::trace() {
  setupImage();

  HitRecord hit_record;
  auto meshes_in_scene = m_scene.getMeshesInScene();
  auto canvas_height = m_canvas.getHeight();
  auto canvas_width = m_canvas.getWidth();

  for (int y = canvas_height - 1; y >= 0; --y) {
	// cannoli::progressBar(1 - (static_cast<float>(y) / static_cast<float>(canvas_height)));
	std::cout << fmt::format("Progress: {}\n", static_cast<int>((1 - (static_cast<float>(y) / static_cast<float>(canvas_height))) * 100));
	for (int x = 0; x < canvas_width; ++x) {
	  resetPixel();
	  for (int s = 0; s < m_samples; ++s) {
		if (m_hitBackground) {
		  m_hitBackground = false;
		  continue;
		}
		Vec3f dir = generateDirection(x, y);
		LightRay ray = emitRay(m_camera.getOrigin(), dir);
		m_pixelColor += renderPixel(ray, m_maxBounces, hit_record, infinity, meshes_in_scene);
	  }
	  writePPMImage(m_ppmImage, m_samples);
	}
  }
  m_ppmImage.close();
}

cannoli::ColorRGB cannoli::RayTracer::renderPixel(cannoli::LightRay &ray,
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
	 m_pixelColor += ColorRGB(0, 0, 0);
  }

  for (const auto &mesh : meshes_in_scene) {
	int nr_of_triangles = mesh->getFaceCount();
	if (mesh->getAABB()->computeAABBIntersection(ray, eps, closest_so_far)) {
	  for (int i = 0; i < nr_of_triangles; ++i) {
		if (mesh->computeTriangleIntersection(ray, eps, closest_so_far, temp_hit_record, i)) {
		  closest_mesh = mesh;
		  closest_so_far = temp_hit_record.t < closest_so_far ? temp_hit_record.t : closest_so_far;
		  hit_record = temp_hit_record;
		  hit_triangle = true;
		  m_hitBackground = false;
		}
	  }
	}
  }
  if (hit_triangle) {
	LightRay scattered_ray = closest_mesh->computeSurfaceInteraction(ray, hit_record);
	ColorRGB albedo = closest_mesh->getMaterial()->getAlbedo();
	return 1.1 * albedo * renderPixel(scattered_ray, n_bounces - 1, hit_record, closest_so_far, meshes_in_scene);
  }
  m_hitBackground = true;
  return paintBackground(ray);
}

void cannoli::RayTracer::writePPMImage(std::ofstream &stream, int samples) {
  float r = m_pixelColor.getX();
  float g = m_pixelColor.getY();
  float b = m_pixelColor.getZ();
  auto scale = 1.0 / samples;

  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  stream << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		 << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void cannoli::RayTracer::setupImage() {
  m_ppmImage.open(m_outFile);
  m_ppmImage << "P3\n" << m_canvas.getWidth() << ' ' << m_canvas.getHeight() << "\n255\n";
}

void cannoli::RayTracer::resetPixel() {
  m_pixelColor.setXYZ(0, 0, 0);
}

cannoli::LightRay cannoli::RayTracer::emitRay(const Vec3f &origin, const Vec3f &direction) {
  return cannoli::LightRay(origin, direction);
}

cannoli::Vec3f cannoli::RayTracer::generateDirection(const int pixel_x, const int pixel_y) {
  auto u = (pixel_x + random_float()) / (m_canvas.getWidth() - 1);
  auto v = (pixel_y + random_float()) / (m_canvas.getHeight() - 1);
  Vec3f
	dir = m_camera.getViewportLLC() + m_camera.getHorizontal() * u + m_camera.getVertical() * v - m_camera.getOrigin();
  return dir;
}

cannoli::ColorRGB cannoli::RayTracer::paintBackground(LightRay &ray) {
  cannoli::Vec3f unit_direction = ray.getDirection().normalize();
  float t = 0.5 * (unit_direction.getY() + 1.0);
  return 1.5 * ((1.0 - t) * ColorRGB(1.0, 1.0, 1.0) + t * ColorRGB(0.5, 0.7, 1.0));
}

