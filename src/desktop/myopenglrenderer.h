#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <QObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

#include "../obj/obj.hpp"

class MyOpenGLRenderer : public QObject, protected QOpenGLFunctions_3_3_Core {
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
