#ifndef CANNOLI_INCLUDE_LIGHT_RAY_H_
#define CANNOLI_INCLUDE_LIGHT_RAY_H_

#include "vec3f.h"
#include "point.h"
#include <array>

namespace cannoli {
class LightRay {
 public:
  LightRay() = default;
  LightRay(const PointXYZ &origin, const Vec3f &dir) : m_origin(origin), m_dir(dir) {};
  LightRay(const PointXYZ &origin, const Vec3f &dir, const float t) : m_origin(origin), m_dir(dir), m_time(t) {};

  [[nodiscard]] PointXYZ getOrigin() const {
	return m_origin;
  }

  void setOrigin(const PointXYZ origin) {
	m_origin = origin;
  }

  [[nodiscard]] Vec3f getDirection() const {
	return m_dir;
  }

  void setDirection(const Vec3f dir) {
	m_dir = dir;
  }

  [[nodiscard]] float getTime() const {
	return m_time;
  }

  void setTime(const float t) {
	m_time = t;
  }

  [[nodiscard]] std::array<int, 3> getKVals() {
	return { m_kx, m_ky, m_kz };
  }

  [[nodiscard]] PointXYZ getPosition(const float t) const {
	return (m_origin + m_dir * t);
  }

  Vec3f permuteDirection() {
	m_kz = cannoli::getMaxDimension(cannoli::abs(m_dir));
	m_kx = m_kz + 1;
	if (m_kx == 3) {
	  m_kx = 0;
	}
	m_ky = m_kx + 1;
	if (m_ky == 3) {
	  m_ky = 0;
	}
	return permute(m_dir, m_kx, m_ky, m_kz);
  }

 protected:
  PointXYZ m_origin{};
  Vec3f m_dir{};
  float m_time{};
  int m_kx{}, m_ky{}, m_kz{};

};
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_LIGHT_RAY_H_