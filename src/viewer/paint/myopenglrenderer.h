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
  QColor get_edge_color();
  QColor get_points_color();
};

#endif  // OPENGLRENDERER_H
