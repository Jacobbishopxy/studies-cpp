#if !defined(SHAPE_H)
#define SHAPE_H

#include <iostream>

class Shape
{
  public:
  friend std::ostream& operator<<(std::ostream& out, const Shape& s)
  {
    return s.print(out);
  }

  virtual std::ostream& print(std::ostream& out) const = 0;

  virtual ~Shape() = default;
};

#endif // SHAPE_H
