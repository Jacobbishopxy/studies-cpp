#include <string>

struct Point2D {
  int x;
  int y;
};

class Box {
 private:
  Point2D m_topLeft{};
  Point2D m_bottomRight{};

 public:
  void setTopLeft(Point2D point) { m_topLeft = point; }
  void setBottomRight(Point2D point) { m_bottomRight = point; }
};

class Label {
 private:
  std::string m_text{};
  int m_fontSize{};

 public:
  void setText(const std::string_view str) { m_text = str; }
  void setFontSize(int fontSize) { m_fontSize = fontSize; }
};

class Button : public Box, public Label {};
