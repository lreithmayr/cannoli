#ifndef CANNOLI_SRC_RAY_TRACER_H_
#define CANNOLI_SRC_RAY_TRACER_H_

#include "light_ray.h"
#include "vec3f.h"
#include "color.h"
#include "point.h"
#include "image.h"
#include "camera.h"
#include "object.h"
#include "scene.h"

#include <string>

namespace cannoli {
  class RayTracer {
   public:
	RayTracer(Scene& scene, Camera& camera, Canvas& canvas, std::string& out_fn) :
		m_scene(scene),
		m_canvas(canvas),
		m_camera(camera),
		m_stopTrace(false),
		m_outFile(out_fn) {}

	void Trace();
	void Stop();

	void ComputeRayColor(LightRay& ray, Object*& object);

   private:
	Scene m_scene;
	Canvas m_canvas;
	Camera m_camera;
	ColorRGB m_pixelColor{};
	bool m_stopTrace;
	std::string m_outFile;
  };
}  // namespace cannoli

#endif //CANNOLI_SRC_RAY_TRACER_H_
