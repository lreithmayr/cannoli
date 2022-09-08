#ifndef CANNOLI_INCLUDE_CAMERA_H_
#define CANNOLI_INCLUDE_CAMERA_H_

#include "point.h"
#include "vec3f.h"

#include <cmath>

// Camera CS:
// ^ y
// |
// |
// |
// O------------------> x
// O = (0,0,0)

// O is in the middle of the camera viewport
//
//
//                       			---------------------------------------|
// 									|									   |
// 									|				    ^ y		   		   |
// 									|				    |		     	   |
// 									|				    |		           |
// 									|				    O----> x		   |
// 									|							           |
// 									|				                       |
//									|									   |
// 									|---------------------------------------


namespace cannoli {
  class Camera {
   public:
	Camera(float ar, float f_length, float vert_fov, PointXYZ origin, Vec3f view_dir, Vec3f vec_up)
		: m_aspectRatio(ar),
		  m_focalLength(f_length),
		  m_verticalFOV(vert_fov),
		  m_origin(origin),
		  m_viewDir(view_dir),
		  m_vecUp(vec_up) {
	  InitializeCameraParams();
	}

	void InitializeCameraParams() {
	  float theta = m_verticalFOV * 0.017453;
	  float h = tan(theta * 0.5);
	  m_viewportHeight = 2.0 * h;
	  m_viewportWidth = m_aspectRatio * m_viewportHeight;
	  Vec3f w = (m_origin - m_viewDir).normalize();
	  Vec3f u = cross(m_vecUp, w).normalize();
	  Vec3f v = cross(w, u);

	  m_horizontal = m_viewportWidth * u;
	  m_vertical = m_viewportHeight * v;
	  m_viewportLowerLeft = m_origin - m_horizontal * 0.5 - m_vertical * 0.5 - w;
	}

	[[nodiscard]] PointXYZ GetOrigin() const {
	  return m_origin;
	}

	void SetOrigin(const PointXYZ &origin) {
	  m_origin = origin;
	}

	[[nodiscard]] Vec3f GetViewDirection() const {
	  return m_viewDir;
	}

	void SetViewDirection(const Vec3f &view_dir) {
	  m_viewDir = view_dir;
	}

	[[nodiscard]] PointXYZ GetViewportLLC() const {
	  return m_viewportLowerLeft;
	}

	[[nodiscard]] Vec3f GetHorizontal() const {
	  return m_horizontal;
	}

	[[nodiscard]] Vec3f GetVertical() const {
	  return m_vertical;
	}

   private:
	const float m_aspectRatio;
	const float m_focalLength;
	const float m_verticalFOV;

	float m_viewportHeight{};
	float m_viewportWidth{};

	PointXYZ m_origin;
	Vec3f m_viewDir;
	Vec3f m_vecUp;
	Vec3f m_horizontal;
	Vec3f m_vertical;
	PointXYZ m_viewportLowerLeft;
  };
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_CAMERA_H_
