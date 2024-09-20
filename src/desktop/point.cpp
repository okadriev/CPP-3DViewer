#include "point.h"

Point Point::rotate(float angle_x, float angle_y, float angle_z) {
  return rotateX(angle_x).rotateY(angle_y).rotateZ(angle_z);
}

Point Point::rotateX(float angle) {
  angle -= 180;
  float rad = angle * M_PI / 180.0;
  float cos_a = cos(rad), sin_a = sin(rad);
  x = x;
  y = y * cos_a - z * sin_a;
  z = y * sin_a + z * cos_a;

  return *this;
}

Point Point::rotateY(float angle) {
  angle -= 180;
  float rad = angle * M_PI / 180.0;
  float cos_a = cos(rad), sin_a = sin(rad);
  x = x * cos_a + z * sin_a;
  y = y;
  z = -x * sin_a + z * cos_a;

  return *this;
}

Point Point::rotateZ(float angle) {
  angle -= 180;
  float rad = angle * M_PI / 180.0;
  float cos_a = cos(rad), sin_a = sin(rad);
  x = x * cos_a - y * sin_a;
  y = x * sin_a + y * cos_a;
  z = z;

  return *this;
}

Point Point::move(float dx, float dy, float dz) {
  x = x + dx;
  y = y + dy;
  z = z + dz;

  return *this;
}

Point Point::scale(float factor) {
  x *= factor;
  y *= factor;
  z *= factor;

  return *this;
}