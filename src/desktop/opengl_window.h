#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>  // не нужен
#include <QOpenGLWidget>
#include <QTimer>  // не нужен
#include <QWidget>

#include "../obj/obj.hpp"
#include "figure.h"

class OpenGLwindow : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  explicit OpenGLwindow(QWidget *parent = nullptr);

  void initializeGL();
  void paintGL();

 private:
  GLuint *shader_program;

  // void resizeGL(int w, int h);

  void setup_Shaders();
  void check_shader_compile(GLuint shader, const char *shader_type);
  void check_program_link(GLuint program);
  QColor get_color();
};

#endif  // OPENGL_WINDOW_H
