#include "point.h"

Point Point::rotate(float angle_x, float angle_y, float angle_z) {
  return rotateX(angle_x).rotateY(angle_y).rotateZ(angle_z);
}

Point Point::rotateX(float angle) {
  angle -= 180;
  float rad = angle * M_PI / 180.0;
  float cos_a = cos(rad), sin_a = sin(rad);
  // qDebug() << "Rotate_x x = " << x << "y = " << y << "z = " << z;
  float y_temp = y;
  y = y * cos_a - z * sin_a;
  z = y_temp * sin_a + z * cos_a;
  // qDebug() << "Rotate_x x = " << x << "y = " << y << "z = " << z;

  return *this;
}

Point Point::rotateY(float angle) {
  angle -= 180;
  float rad = angle * M_PI / 180.0;
  float cos_a = cos(rad), sin_a = sin(rad);
  // qDebug() << "Rotate_y x = " << x << "y = " << y << "z = " << z;
  float x_temp = x;
  x = x * cos_a + z * sin_a;
  z = -x_temp * sin_a + z * cos_a;
  // qDebug() << "Rotate_y x = " << x << "y = " << y << "z = " << z;

  return *this;
}

Point Point::rotateZ(float angle) {
  angle -= 180;
  float rad = angle * M_PI / 180.0;
  float cos_a = cos(rad), sin_a = sin(rad);
  // qDebug() << "Rotate_z x = " << x << "y = " << y << "z = " << z;
  float x_temp = x;
  x = x * cos_a - y * sin_a;
  y = x_temp * sin_a + y * cos_a;
  // qDebug() << "Rotate_z x = " << x << "y = " << y << "z = " << z;

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