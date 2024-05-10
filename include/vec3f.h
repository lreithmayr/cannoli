#ifndef CANNOLI_INCLUDE_VEC3F_H_
#define CANNOLI_INCLUDE_VEC3F_H_

#include "utils.h"
#include "obj_file_loader.h"

#include <cmath>
#include <iostream>
#include <array>

namespace cannoli {
class Vec3f {
 public:
  Vec3f() : m_vec{0, 0, 0} {
  }
  Vec3f(float x, float y, float z) : m_vec{x, y, z} {
  }

  void setXYZ(float x, float y, float z) {
	m_vec[0] = x;
	m_vec[1] = y;
	m_vec[2] = z;
  }

  [[nodiscard]] float getX() const {
	return m_vec[0];
  }

  void setX(const float x) {
	m_vec[0] = x;
  }

  [[nodiscard]] float getY() const {
	return m_vec[1];
  }

  void setY(const float y) {
	m_vec[0] = y;
  }

  [[nodiscard]] float getZ() const {
	return m_vec[2];
  }

  void setZ(const float z) {
	m_vec[0] = z;
  }

  float operator[](const int i) const {
	return m_vec.at(i);
  }

  Vec3f operator*(const float &f) const {
	return {m_vec[0] * f, m_vec[1] * f, m_vec[2] * f};
  }

  Vec3f operator*(const Vec3f &vec) const {
	return {m_vec[0] * vec[0], m_vec[1] * vec[1], m_vec[2] * vec[2]};
  }

  Vec3f &operator*=(const double t) {
	m_vec[0] *= t;
	m_vec[1] *= t;
	m_vec[2] *= t;
	return *this;
  }

  Vec3f operator+(const Vec3f &vec) const {
	return {m_vec[0] + vec[0], m_vec[1] + vec[1], m_vec[2] + vec[2]};
  }

  Vec3f &operator+=(const Vec3f &v) {
	m_vec[0] += v[0];
	m_vec[1] += v[1];
	m_vec[2] += v[2];
	return *this;
  }

  Vec3f operator-() const {
	return {-m_vec[0], -m_vec[1], -m_vec[2]};
  }

  Vec3f operator-(const Vec3f &vec) const {
	return {m_vec[0] - vec[0], m_vec[1] - vec[1], m_vec[2] - vec[2]};
  }

  friend std::ostream &operator<<(std::ostream &out, Vec3f &vec) {
	return out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
  }

  [[nodiscard]] float computeLength() const {
	return (std::sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]));
  }

  [[nodiscard]] float computeLengthSquared() const {
	return (m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]);
  }

  [[nodiscard]] Vec3f cross(Vec3f &vec) const {
	return {m_vec[1] * vec[2] - m_vec[2] * vec[1], m_vec[2] * vec[0] - m_vec[0] * vec[2],
			m_vec[0] * vec[1] - m_vec[1] * vec[0]};
  }

  [[nodiscard]] Vec3f normalize() const {
	return (*this * (1 / this->computeLength()));
  }

  static Vec3f random() {
	return Vec3f{random_float(), random_float(), random_float()};
  }

  static Vec3f random(float min, float max) {
	return Vec3f{random_float(min, max), random_float(min, max), random_float(min, max)};
  }

  static Vec3f computeRandWithinUnitSphere() {
	while (true) {
	  auto p = Vec3f::random(-1, 1);
	  if (p.computeLengthSquared() >= 1) {
		continue;
	  }
	  return p;
	}

  }

 private:
  std::array<float, 3> m_vec;
};

// Inlined functions (non-member functions)

[[nodiscard]] inline Vec3f operator*(const float &f, const Vec3f &vec) {
  return {f * vec[0], f * vec[1], f * vec[2]};
}

[[nodiscard]] inline float dot(const Vec3f &vec1, const Vec3f &vec2) {
  return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

[[nodiscard]] inline Vec3f cross(const Vec3f &vec1, const Vec3f &vec2) {
  return {vec1[1] * vec2[2] - vec1[2] * vec2[1], vec1[2] * vec2[0] - vec1[0] * vec2[2],
		  vec1[0] * vec2[1] - vec1[1] * vec2[0]};
}

[[nodiscard]] inline Vec3f permute(const Vec3f &vec, const int x, const int y, const int z) {
  return {vec[x], vec[y], vec[z]};
}

inline Vec3f yawPitchToXYZ(const float &yaw, const float &pitch) {
  float cos_pitch = cos(pitch);
  float x = cos(yaw) * cos_pitch;
  float y = sin(yaw) * cos_pitch;
  float z = sin(pitch);
  return {x, y, z};
}

// Returns the index of the largest value in the vector
inline int getMaxDimension(const Vec3f &vec) {
  int max = 0;
  if (vec[1] > vec[0] && vec[1] > vec[2]) {
	max = 1;
  }
  if (vec[2] > vec[0] && vec[2] > vec[1]) {
	max = 2;
  }
  return max;
}

inline Vec3f abs(const Vec3f &vec) {
  return {std::abs(vec[0]), std::abs(vec[1]), std::abs(vec[2])};
}

// Inlined functions providing interop with Vector3 struct from objl namespace

[[nodiscard]] inline Vec3f vec3ToVec3f(const objl::Vector3 &objl_vector3) {
  return {objl_vector3.X, objl_vector3.Y, objl_vector3.Z};
}


}  // namespace cannoli

// fmt formatter for Vec3f type
template <> struct fmt::formatter<cannoli::Vec3f> {
  // Presentation format: 'f' - fixed, 'e' - exponential.
  char presentation = 'f';

  // Parses format specifications of the form ['f' | 'e'].
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
	auto it = ctx.begin(), end = ctx.end();
	if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

	// Check if reached the end of the range:
	if (it != end && *it != '}') throw format_error("invalid format");

	// Return an iterator past the end of the parsed range:
	return it;
  }

  // Formats the point p using the parsed format specification (presentation)
  // stored in this formatter.
  template <typename FormatContext>
  auto format(const cannoli::Vec3f& v, FormatContext& ctx) const -> decltype(ctx.out()) {
	// ctx.out() is an output iterator to write to.
	return presentation == 'f'
		   ? fmt::format_to(ctx.out(), "(x = {:.1f}, y = {:.1f}, z = {:.1f})", v.getX(), v.getY(), v.getZ())
		   : fmt::format_to(ctx.out(), "(x = {:.1e}, y = {:.1e}, z = {:.1f})", v.getX(), v.getY(), v.getZ());
  }
};
#endif //CANNOLI_INCLUDE_VEC3F_H_
