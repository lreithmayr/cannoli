#ifndef CANNOLI_INCLUDE_CANVAS_H_
#define CANNOLI_INCLUDE_CANVAS_H_

namespace cannoli {
class Canvas {
 public:
  Canvas() = default;
  void initialize() {
	m_height = static_cast<int>(m_width / m_aspectRatio);
  }

  void setAspectRation(float aspect_ratio) {
	m_aspectRatio = aspect_ratio;
  }

  void setWidth(float width) {
	m_width = width;
  }

  [[nodiscard]] int getHeight() const {
	return m_height;
  }

  [[nodiscard]] int getWidth() const {
	return m_width;
  }

 private:
  float m_aspectRatio{};
  int m_width{};
  int m_height{};
};
} // namespace cannoli
#endif //CANNOLI_INCLUDE_CANVAS_H_
