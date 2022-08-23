#ifndef CANNOLI_SRC_RAY_TRACER_H_
#define CANNOLI_SRC_RAY_TRACER_H_

#include "light_ray.h"
#include "vec3f.h"
#include "color.h"
#include "point.h"
#include "image.h"
#include "camera.h"

#include <string>

namespace cannoli {
  class RayTracer {
   public:
	RayTracer(Camera& camera, Image& img, std::string& out_fn) :
		m_img(img),
		m_camera(camera),
		m_stopTrace(false),
		m_outFile(out_fn) {}
	~RayTracer() = default;

	void Trace();
	void Stop();

	// Send rays through pixels and compute the color along the way
	void CastRay(const Vec3f& dir);

	void ComputeRayColor(LightRay& ray);

   private:
	Image m_img;
	Camera m_camera;
	ColorRGB m_pixelColor{};
	bool m_stopTrace;
	std::string m_outFile;
  };
}

#endif //CANNOLI_SRC_RAY_TRACER_H_
