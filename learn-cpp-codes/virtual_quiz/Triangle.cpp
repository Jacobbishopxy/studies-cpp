#include "Triangle.h"

#include <iostream>

std::ostream& Triangle::print(std::ostream& out) const
{
  out << "Triangle(" << this->m_x << ", " << this->m_y << ", " << this->m_z
      << ")";
  return out;
}
