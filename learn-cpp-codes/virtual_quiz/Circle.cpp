#include "Circle.h"

#include <iostream>

std::ostream& Circle::print(std::ostream& out) const
{
  out << "Circle(" << this->m_centre << ", radius " << m_radius << ")";
  return out;
}

int Circle::getRadius() const { return this->m_radius; }