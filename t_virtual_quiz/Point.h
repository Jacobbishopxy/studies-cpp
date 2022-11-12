#if !defined(POINT_H)
#define POINT_H

#include <iostream>

struct Point {
  int m_x;
  int m_y;

  Point(int x, int y) : m_x{x}, m_y{y} {}

  friend std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << "Point(" << p.m_x << ", " << p.m_y << ')';
  }
};

#endif  // POINT_H
