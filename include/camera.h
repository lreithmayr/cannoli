#ifndef CANNOLI_INCLUDE_CAMERA_H_
#define CANNOLI_INCLUDE_CAMERA_H_

#include "point.h"
#include "vec3f.h"

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
	Camera(float ar, float vp_height, float f_length)
		: m_aspectRatio(ar),
		  m_viewportHeight(vp_height),
		  m_viewportWidth(m_aspectRatio * m_viewportHeight),
		  m_focalLength(f_length),
		  m_origin(cannoli::PointXYZ(0, 0, 0)),
		  m_horizontal(cannoli::Vec3f(m_viewportWidth, 0, 0)),
		  m_vertical(cannoli::Vec3f(0, m_viewportHeight, 0)),
		  m_viewportLowerLeft(m_origin - m_horizontal*0.5 - m_vertical*0.5 - Vec3f(0, 0, m_focalLength)
		  ) {}

	[[nodiscard]] PointXYZ GetOrigin() const {
	  return m_origin;
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
	const float m_viewportHeight;
	const float m_viewportWidth;
	const float m_focalLength;

	const PointXYZ m_origin;
	const Vec3f m_horizontal;
	const Vec3f m_vertical;
	const PointXYZ
		m_viewportLowerLeft;
  };
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_CAMERA_H_
