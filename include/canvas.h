#ifndef CANNOLI_INCLUDE_CANVAS_H_
#define CANNOLI_INCLUDE_CANVAS_H_

namespace cannoli {
struct Canvas {
  Canvas(float ar, int w) : aspect_ratio(ar), width(w) {};

  const float aspect_ratio;
  const int width;
  const int height = static_cast<int>(width / aspect_ratio);
};
}
#endif //CANNOLI_INCLUDE_CANVAS_H_
