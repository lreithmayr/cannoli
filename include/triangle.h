#ifndef CANNOLI_SRC_TRIANGLE_H_
#define CANNOLI_SRC_TRIANGLE_H_

#include <utility>

#include "object.h"

namespace cannoli {
class Triangle : public Object {
 public:
  Triangle() = default;
  explicit Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2) : m_v0(v0), m_v1(v1), m_v2(v2) {};
  ~Triangle() override = default;

  bool Hit(const LightRay &ray, const float &t_min, const float &t_max, HitRecord &hit_record) override;
  cannoli::LightRay ComputeSurfaceInteraction(const LightRay &ray, HitRecord &hit_record) override;

 private:
  Vec3f m_v0;
  Vec3f m_v1;
  Vec3f m_v2;
};

} // namespace cannoli
#endif //CANNOLI_SRC_TRIANGLE_H_
