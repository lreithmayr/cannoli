#ifndef CANNOLI_INCLUDE_CAMERA_H_
#define CANNOLI_INCLUDE_CAMERA_H_

#include "point.h"
#include "vec3f.h"

#include <cmath>

namespace cannoli {
class Camera {
 public:
  Camera() = default;

  void initialize() {
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

  void setAspectRatio(float aspect_ratio) {
	m_aspectRatio = aspect_ratio;
  }

  void setFocalLength(float focal_length) {
	m_focalLength = focal_length;
  }

  void setVerticalFOV(float vert_fov) {
	m_verticalFOV = vert_fov;
  }

  [[nodiscard]] PointXYZ getOrigin() const {
	return m_origin;
  }

  void setOrigin(const PointXYZ &origin) {
	m_origin = origin;
  }

  [[nodiscard]] Vec3f getViewDirection() const {
	return m_viewDir;
  }

  void setViewDirection(const Vec3f &view_dir) {
	m_viewDir = view_dir;
  }

  void setUp(Vec3f up){
	m_vecUp = up;
  }

  [[nodiscard]] PointXYZ getViewportLLC() const {
	return m_viewportLowerLeft;
  }

  [[nodiscard]] Vec3f getHorizontal() const {
	return m_horizontal;
  }

  [[nodiscard]] Vec3f getVertical() const {
	return m_vertical;
  }

 private:
  float m_aspectRatio{};
  float m_focalLength{};
  float m_verticalFOV{};

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
