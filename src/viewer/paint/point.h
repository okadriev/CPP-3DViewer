#ifndef POINT_H
#define POINT_H

#define _USE_MATH_DEFINES
#include <QDebug>  // убрать
#include <cmath>

class Point {
 private:
 public:
  float x, y, z;

  Point(float _x = 0, float _y = 0, float _z = 0) { x = _x, y = _y, z = _z; };
  Point rotateX(float angle);
  Point rotateY(float angle);
  Point rotateZ(float angle);
  Point rotate(float angle_x, float angle_y, float angle_z);
  Point move(float dx, float dy, float dz);
  Point scale(float factor);
};

#endif  // POINT_H
