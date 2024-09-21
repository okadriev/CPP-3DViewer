#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

// #define GL_SILENCE_DEPRECATION

#include <QMessageBox>
// #include <QWheelEvent>
#include <QObject>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

#include "../obj/obj.hpp"

class MyOpenGLRenderer : public QObject, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit MyOpenGLRenderer(QOpenGLWidget *glWidget, QObject *parent = nullptr);

  void initializeGL();
  void paintGL();
  //   void resizeGL(int w, int h);

 private:
  QOpenGLWidget *m_glWidget;
  GLuint *shader_program;

  QColor get_color();
  void setup_Shaders();
  void check_shader_compile(GLuint shader, const char *shader_type);
  void check_program_link(GLuint program);
};

#endif  // OPENGLRENDERER_H
