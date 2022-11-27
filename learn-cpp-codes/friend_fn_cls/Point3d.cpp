
// Point3d
#include "Point3d.h"
// 函数 moveByVector()
#include "Vector3d.h"

#include <iostream>

Point3d::Point3d(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {}

void Point3d::print() const { std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n"; }

void Point3d::moveByVector(const Vector3d& v)
{
  m_x += v.m_x;
  m_y += v.m_y;
  m_z += v.m_z;
}
