#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>

// 前向声明
class Vector3d;

class Point3d
{
  private:
  double m_x{};
  double m_y{};
  double m_z{};

  public:
  Point3d(double x = 0.0, double y = 0.0, double z = 0.0);

  void print() const;

  // 使用 Vector3d 的前向声明
  void moveByVector(const Vector3d& v);

  void moveByVectorPro(const Vector3d& v);
};

#endif
