#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

#include "../obj/obj.hpp"
#include "figure.h"

class OpenGL_window : public QOpenGLWidget, protected QOpenGLExtraFunctions {
 public:
  OpenGL_window(QWidget *parent);

 private:
  GLuint *shader_program;
  //    Figure fig;

  void paintGL();
  void initializeGL();
  // void resizeGL(int w, int h);

  void setup_Shaders();
  void check_shader_compile(GLuint shader, const char *shader_type);
  void check_program_link(GLuint program);
  QColor get_color();
};

#endif  // OPENGL_WINDOW_H
