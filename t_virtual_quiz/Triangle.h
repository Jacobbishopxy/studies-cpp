#if !defined(TRIANGLE_H)
#define TRIANGLE_H

#include "Point.h"
#include "Shape.h"

class Triangle : public Shape {
 private:
  Point m_x;
  Point m_y;
  Point m_z;

 public:
  Triangle(Point x, Point y, Point z) : m_x{x}, m_y{y}, m_z{z} {}

  std::ostream& print(std::ostream& out) const override;
};

#endif  // TRIANGLE_H
