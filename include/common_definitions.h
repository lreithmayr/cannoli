#ifndef CANNOLI_INCLUDE_COMMON_DEFINITIONS_H_
#define CANNOLI_INCLUDE_COMMON_DEFINITIONS_H_

#include<cmath>
#include <limits>

// Constants

const float infinity = std::numeric_limits<double>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline float deg_to_rad(double deg) {
  return deg * pi / 180.0;
}
#endif //CANNOLI_INCLUDE_COMMON_DEFINITIONS_H_
