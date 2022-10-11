#ifndef CANNOLI_INCLUDE_LIGHT_RAY_H_
#define CANNOLI_INCLUDE_LIGHT_RAY_H_

#include "vec3f.h"
#include "point.h"

namespace cannoli {
class LightRay {
 public:
  LightRay() = default;
  LightRay(const PointXYZ &origin, const Vec3f &dir) : m_origin(origin), m_dir(dir) {};
  LightRay(const PointXYZ &origin, const Vec3f &dir, const float t) : m_origin(origin), m_dir(dir), m_time(t) {};

  [[nodiscard]] PointXYZ GetOrigin() const
  {
	return m_origin;
  }

  void SetOrigin(const PointXYZ origin)
  {
	m_origin = origin;
  }

  [[nodiscard]] Vec3f GetDirection() const
  {
	return m_dir;
  }

  void SetDirection(const Vec3f dir)
  {
	m_dir = dir;
  }

  [[nodiscard]] float GetTime() const
  {
	return m_time;
  }

  void SetTime(const float t)
  {
	m_time = t;
  }

  [[nodiscard]] PointXYZ Position(const float t) const
  {
	return (m_origin + m_dir * t);
  }

 protected:
  PointXYZ m_origin{};
  Vec3f m_dir{};
  float m_time{};

};
}  // namespace cannoli

#endif //CANNOLI_INCLUDE_LIGHT_RAY_H_