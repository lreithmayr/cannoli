#ifndef CANNOLI_INCLUDE_COLOR_H_
#define CANNOLI_INCLUDE_COLOR_H_

#include "vec3f.h"
#include <fstream>

namespace cannoli {
  typedef cannoli::Vec3f ColorRGB;

  void WritePPMImage(std::ofstream& stream, ColorRGB pixel_color) {
	stream << static_cast<int>(255.999 * pixel_color.x()) << ' '
		   << static_cast<int>(255.999 * pixel_color.y()) << ' '
		   << static_cast<int>(255.999 * pixel_color.z()) << '\n';
  }
}

#endif //CANNOLI_INCLUDE_COLOR_H_