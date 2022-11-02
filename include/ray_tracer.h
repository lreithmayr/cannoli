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
  RayTracer(Scene scene,
			const Camera &camera,
			const Canvas &canvas,
			std::string &out_fn,
			int samples,
			int max_bounces) :
	m_scene(std::move(scene)),
	m_canvas(canvas),
	m_camera(camera),
	m_stopTrace(false),
	m_outFile(out_fn),
	m_samples(samples),
	m_maxBounces(max_bounces) {
	SetUp();
  }

  void SetUp();
  void ResetPixel();

  LightRay EmitRay(int pixel_x, int pixel_y);
  void Trace();

  cannoli::ColorRGB ComputeColor(const LightRay &ray,
								 int n_bounces,
								 HitRecord &hit_record,
								 float t_max,
								 std::vector<Triangle> &triangles);

  void WritePPMImage(std::ofstream &stream, int samples);

 private:
  Scene m_scene;
  Canvas m_canvas;
  Camera m_camera;
  std::ofstream m_ppmImage;
  ColorRGB m_pixelColor{};
  bool m_stopTrace;
  std::string m_outFile;
  int m_samples;
  int m_maxBounces;
};
}  // namespace cannoli

#endif //CANNOLI_SRC_RAY_TRACER_H_