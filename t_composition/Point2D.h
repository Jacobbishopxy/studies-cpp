#if !defined(POINT2D_H)
#define POINT2D_H

#include <iostream>

class Point2D {
  int m_x;
  int m_y;

public:
  // 默认构造函数
  Point2D() : m_x{0}, m_y{0} {}

  // 指定构造函数
  Point2D(int x, int y) : m_x{x}, m_y{y} {}

  // 重载输出操作符
  friend std::ostream &operator<<(std::ostream &out, const Point2D &point) {
    out << '(' << point.m_x << ", " << point.m_y << ')';
    return out;
  }

  void setPoint(int x, int y) {
    m_x = x;
    m_y = y;
  }
};

#endif // POINT2D_H
