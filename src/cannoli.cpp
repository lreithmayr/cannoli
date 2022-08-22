#include "color.h"

#include <iostream>

int main() {
  const int img_width = 256;
  const int img_height = 256;

  std::ofstream ppm_image;
  ppm_image.open("../images/image.ppm");
  ppm_image << "P3\n" << img_width << ' ' << img_height << "\n255\n";

  for (int i = img_height - 1; i >= 0; i--) {
	for (int j = 0; j < img_width; j++) {
	  cannoli::ColorRGB pixel_color(float(j) / (img_width - 1), float(i) / (img_height - 1), 0.25);
	  std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
	  cannoli::WritePPMImage(ppm_image, pixel_color);
	}
  }
  std::cerr << "\n Done! \n";
  ppm_image.close();
}
