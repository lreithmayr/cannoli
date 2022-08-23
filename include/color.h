#ifndef CANNOLI_INCLUDE_COLOR_H_
#define CANNOLI_INCLUDE_COLOR_H_

#include "vec3f.h"
#include <fstream>

namespace cannoli {
  typedef Vec3f ColorRGB;

  void WritePPMImage(std::ofstream& stream, ColorRGB pixel_color) {
	stream << static_cast<int>(255.999 * pixel_color.GetX()) << ' '
		   << static_cast<int>(255.999 * pixel_color.GetY()) << ' '
		   << static_cast<int>(255.999 * pixel_color.GetZ()) << '\n';
  }
}

#endif //CANNOLI_INCLUDE_COLOR_H_