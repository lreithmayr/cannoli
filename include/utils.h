#ifndef CANNOLI_INCLUDE_UTILS_H_
#define CANNOLI_INCLUDE_UTILS_H_

#include <fmt/format.h>
#include <cmath>
#include <limits>
#include <random>
#include <iostream>

// Assorted useful things

namespace cannoli {

void ProgressBar(auto progress) {
  int barWidth = 70;

  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
	if (i < pos) {
	  std::cout << "=";
	} else if (i == pos) {
	  std::cout << ">";
	} else {
	  std::cout << " ";
	}
  }
  std::cout << "] " << static_cast<int>(progress * 100.0) << " %\r";
  std::cout.flush();
}

// Constants

const float infinity = std::numeric_limits<double>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline float deg_to_rad(double deg) {
  return deg * pi / 180.0;
}

inline float clamp(float x, float min, float max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

inline float random_float() {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(mt);
}

inline float random_float(float min, float max) {
  return min + (max - min) * random_float();
}

} // namespace cannoli
#endif //CANNOLI_INCLUDE_UTILS_H_
