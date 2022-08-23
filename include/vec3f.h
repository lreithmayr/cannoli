#ifndef CANNOLI_INCLUDE_VEC3F_H_
#define CANNOLI_INCLUDE_VEC3F_H_

#include <cmath>
#include <iostream>

namespace cannoli {
  class Vec3f {
   public:
	Vec3f() : m_vec{0, 0, 0} {
	}
	Vec3f(float x, float y, float z) : m_vec{x, y, z} {
	}

	[[nodiscard]] float GetX() const {
	  return m_vec[0];
	}

	void SetX(const float x) {
	  m_vec[0] = x;
	}

	[[nodiscard]] float GetY() const {
	  return m_vec[1];
	}

	void SetY(const float y) {
	  m_vec[0] = y;
	}

	[[nodiscard]] float GetZ() const {
	  return m_vec[2];
	}

	void SetZ(const float z) {
	  m_vec[0] = z;
	}

	float operator[](const int i) const {
	  return m_vec[i];
	}

	Vec3f operator*(const float& f) const {
	  return {m_vec[0] * f, m_vec[1] * f, m_vec[2] * f};
	}

	Vec3f operator*(const Vec3f& vec) const {
	  return {m_vec[0] * vec[0], m_vec[1] * vec[1], m_vec[2] * vec[2]};
	}

	Vec3f operator+(const Vec3f& vec) const {
	  return {m_vec[0] + vec[0], m_vec[1] + vec[1], m_vec[2] + vec[2]};
	}

	Vec3f operator-() const {
	  return {-m_vec[0], -m_vec[1], -m_vec[2]};
	}

	Vec3f operator-(const Vec3f& vec) const {
	  return {m_vec[0] - vec[0], m_vec[1] - vec[1], m_vec[2] - vec[2]};
	}

	friend std::ostream& operator<<(std::ostream& out, Vec3f& vec) {
	  return out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
	}

	[[nodiscard]] float length() const {
	  return (std::sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]));
	}

	[[nodiscard]] float dot(Vec3f& vec) {
	  return (m_vec[0] * vec[0] + m_vec[1] * vec[1] + m_vec[2] * vec[2]);
	}

	[[nodiscard]] Vec3f cross(Vec3f& vec) const {
	  return {
		  m_vec[1] * vec[2] - m_vec[2] * vec[1],
		  m_vec[2] * vec[0] - m_vec[0] * vec[2],
		  m_vec[0] * vec[1] - m_vec[1] * vec[0]
	  };
	}

	[[nodiscard]] Vec3f normalize() const {
	  return (*this * (1 / this->length()));
	}

   protected:
	float m_vec[3];
  };

// Free utility functions (non-member functions)

  Vec3f operator*(const float& f, const Vec3f& vec) {
	return {f * vec[0], f * vec[1], f * vec[2]};
  }

}
#endif //CANNOLI_INCLUDE_VEC3F_H_
