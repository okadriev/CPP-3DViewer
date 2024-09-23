#include "myopenglrenderer.h"

MyOpenGLRenderer::MyOpenGLRenderer(QOpenGLWidget *glWidget, QObject *parent)
    : QObject(parent), m_glWidget(glWidget) {
  shader_program = new GLuint;
}

void MyOpenGLRenderer::initializeGL() {
  // qDebug() << "MyOpenGLRenderer::initializeGL called";
  m_glWidget->makeCurrent();
  initializeOpenGLFunctions();
  SettingInfo &settings = *settinginfo();
  QColor color = get_color();
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Figure fig = get_figure()->normalize();
  glVertexPointer(3, GL_FLOAT, 0, fig.points.data());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* if (this->projection_type == 0) {
    glFrustum(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
              1 * normalize_coef, normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, 0, -2 * normalize_coef);
    glRotatef(30, 1, 0, 0);
  } else {
    glOrtho(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
            1 * normalize_coef, -1 * normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, -normalize_coef / 2, 0);
  } */ //проекция

  glEnableClientState(GL_VERTEX_ARRAY);

  if (settings.vertex_type) {
    if (settings.vertex_type == 1) {
      // glEnable(GL_POINT_SMOOTH);
      glEnable(GL_POINT_SMOOTH_HINT);
    }
    glPointSize(settings.vertex_size);
    color = get_points_color();
    glColor3f(color.redF(), color.greenF(), color.blueF());
    glDrawArrays(GL_POINTS, 0, fig.points.size() / 3);
    if (settings.vertex_type == 1) {
      // glDisable(GL_POINT_SMOOTH);
      glDisable(GL_POINT_SMOOTH_HINT);
    }
  }

  if (settinginfo()->edges_type) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(get_line_thickness());
  color = get_edge_color();
  glColor3f(color.redF(), color.greenF(), color.blueF());
  glDrawElements(GL_LINES, fig.edges.size(), GL_UNSIGNED_INT, fig.edges.data());
  if (settinginfo()->edges_type) {
    glDisable(GL_LINE_STIPPLE);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyOpenGLRenderer::paintGL() {
  // qDebug() << "MyOpenGLRenderer::paintGL called";
}

// void MyOpenGLRenderer::resizeGL(int w, int h) {
//   glViewport(0, 0, w, h);
//   // Дополнительный код для обработки изменения размера
// }

QColor MyOpenGLRenderer::get_color() {
  SettingInfo *info = settinginfo();
  return (info->background_color && !info->background_color->empty())
             ? QColor(QString::fromStdString(*info->background_color))
             : QColor();
}

QColor MyOpenGLRenderer::get_edge_color() {
  SettingInfo *info = settinginfo();
  return (info->edge_color && !info->edge_color->empty())
             ? QColor(QString::fromStdString(*info->edge_color))
             : QColor();
}

QColor MyOpenGLRenderer::get_points_color() {
  SettingInfo *info = settinginfo();
  return (info->vertex_color && !info->vertex_color->empty())
             ? QColor(QString::fromStdString(*info->vertex_color))
             : QColor();
}

float MyOpenGLRenderer::get_line_thickness() {
  GLfloat lineWidthRange[2];
  GLfloat lineWidthGranularity;

  glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);
  glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &lineWidthGranularity);

  float thickness = (lineWidthRange[1] - lineWidthRange[0]) /
                        lineWidthGranularity * settinginfo()->edge_thickness +
                    lineWidthRange[0];

  return thickness;
}