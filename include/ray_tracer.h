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
  cannoli::ColorRGB renderPixel(
	cannoli::LightRay &ray,
	int n_bounces,
	HitRecord &hit_record,
	float t_max,
	std::vector<std::shared_ptr<Mesh>> &meshes_in_scene);
  void WritePPMImage(std::ofstream &stream, int samples);
  void SetupImage();
  void ResetPixel();
  Vec3f GenerateDirection(int pixel_x, int pixel_y);
  static LightRay EmitRay(const Vec3f &origin, const Vec3f &direction);
  static cannoli::ColorRGB PaintBackground(cannoli::LightRay &ray);

 private:
  std::ofstream m_ppmImage{};
  Scene m_scene;
  Canvas m_canvas;
  Camera m_camera;
  ColorRGB m_pixelColor{};
  bool m_stopTrace;
  std::string m_outFile;
  int m_samples;
  int m_maxBounces;

  bool m_hitBackground{false};
};
}  // namespace cannoli

#endif //CANNOLI_SRC_RAY_TRACER_H_