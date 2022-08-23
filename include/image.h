#ifndef CANNOLI_INCLUDE_IMAGE_H_
#define CANNOLI_INCLUDE_IMAGE_H_



namespace cannoli {
  struct Image {
	Image(float ar, int w): aspect_ratio(ar), width(w) {};

	const float aspect_ratio;
	const int width;
	const int height = int(width / aspect_ratio);
  };
}
#endif //CANNOLI_INCLUDE_IMAGE_H_
