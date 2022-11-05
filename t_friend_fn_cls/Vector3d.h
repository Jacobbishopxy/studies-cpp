#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3d.h" // 使用 Point3d::moveByVector() 作为友元

class Vector3d {
private:
  double m_x{};
  double m_y{};
  double m_z{};

public:
  Vector3d(double x = 0.0, double y = 0.0, double z = 0.0);

  void print() const;

  friend void Point3d::moveByVector(const Vector3d& v);
};

#endif
