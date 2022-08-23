#include "ray_tracer.h"

#include <iostream>

#define ASPECT_RATIO 16.0/9.0
#define IMG_WIDTH 400
#define VIEWPORT_HEIGHT 2.0
#define FOCAL_LENGTH 1.0

int main() {
  std::string out_path = "../images/traced.ppm";

  cannoli::Camera camera(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH);
  cannoli::Image image(ASPECT_RATIO, IMG_WIDTH);
  cannoli::RayTracer rt(camera, image, out_path);

  rt.Trace();
}
