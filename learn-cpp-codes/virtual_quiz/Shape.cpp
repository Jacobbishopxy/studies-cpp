
#include "Shape.h"

#include <iostream>

std::ostream& Shape::print(std::ostream& out) const
{
  out << "Base";
  return out;
}
