#if !defined(CIRCLE_H)
#define CIRCLE_H

#include "Point.h"
#include "Shape.h"

class Circle : public Shape {
 private:
  Point m_centre;
  int m_radius;

 public:
  Circle(Point centre, int radius) : m_centre{centre}, m_radius{radius} {}

  std::ostream& print(std::ostream& out) const override;
};

#endif  // CIRCLE_H
