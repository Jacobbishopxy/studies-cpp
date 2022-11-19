#include "Vector3d.h"
#include <iostream>

Vector3d::Vector3d(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {}

void Vector3d::print() const { std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n"; }
