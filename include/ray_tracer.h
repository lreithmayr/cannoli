#ifndef CANNOLI_SRC_RAY_TRACER_H_
#define CANNOLI_SRC_RAY_TRACER_H_

#include "utils.h"
#include "light_ray.h"
#include "vec3f.h"
#include "color.h"
#include "point.h"
#include "canvas.h"
#include "camera.h"
#include "scene.h"
#include "hit_record.h"
#include "mesh.h"

#include <string>
#include <utility>

namespace cannoli {
class RayTracer {
 public:
  RayTracer() = default;

  void trace();
  ColorRGB renderPixel(
	cannoli::LightRay &ray,
	int n_bounces,
	HitRecord &hit_record,
	float t_max,
	std::vector<std::shared_ptr<Mesh>> &meshes_in_scene);
  void writePPMImage(std::ofstream &stream, int samples);
  void setupImage();
  void resetPixel();
  Vec3f generateDirection(int pixel_x, int pixel_y);
  static LightRay emitRay(const Vec3f &origin, const Vec3f &direction);
  static cannoli::ColorRGB paintBackground(LightRay &ray);

  void loadScene(Scene &scene) {
	m_scene = scene;
  }
  void setCamera(Camera &camera) {
	m_camera = camera;
  }
  void setCanvas(Canvas &canvas) {
	m_canvas = canvas;
  }
  void setOutputPath(std::string &out_fn) {
	m_outFile = out_fn;
  }
  void setSamples(int samples) {
	m_samples = samples;
  }
  void setMaxBounces(int max_bounces) {
	m_maxBounces = max_bounces;
  }

 private:
  std::ofstream m_ppmImage{};
  Scene m_scene{};
  Canvas m_canvas{};
  Camera m_camera{};
  ColorRGB m_pixelColor{};
  bool m_stopTrace{false};
  std::string m_outFile;
  int m_samples{5};
  int m_maxBounces{5};

  bool m_hitBackground{false};
};
}  // namespace cannoli

#endif //CANNOLI_SRC_RAY_TRACER_H_