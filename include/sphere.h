#ifndef CANNOLI_INCLUDE_SPHERE_H_
#define CANNOLI_INCLUDE_SPHERE_H_

#include "object.h"

namespace cannoli {

class Material;

class Sphere : public Object {
 public:
  Sphere(Vec3f center, float radius, std::shared_ptr<Material> &material) : m_center(center), m_radius(radius) {
    m_type = ObjectType::SPHERE;
    m_material = material;
  }

  // Solves quadratic equation for a light ray with origin A, direction b and time constant t hitting a sphere with
  // given center C and radius r
  // t²*b*b + 2t*b*(A-C) + (A-C)*(A-C) - r² <= 0
  //  a_2 = b*b, a_1 = 2b*(A-C), a_0 = (A-C)(A-C) - r²
  bool Hit(const LightRay &ray, const float &t_min, const float &t_max, HitRecord &hit_record) override;
  Vec3f CalculateSurfaceNormal(const LightRay &ray, float t, HitRecord &hit_record);
  cannoli::LightRay ComputeSurfaceInteraction(const LightRay &ray, HitRecord &hit_record) override;

 protected:
  PointXYZ m_center;
  float m_radius;
};
}  // namespace cannoli
#endif //CANNOLI_INCLUDE_SPHERE_H_
