#include "opengl_window.h"

MyOpenGLwindow::MyOpenGLwindow(QWidget *parent, QOpenGLWidget *_openGLWidget)
    : QOpenGLWidget(parent) {
  shader_program = NULL;
  openGLWidget = _openGLWidget;
}

void MyOpenGLwindow::initializeGL() {
  openGLWidget->makeCurrent();
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Чёрный фон

  // setup_Shaders();
}

void MyOpenGLwindow::paintGL() {
  openGLWidget->makeCurrent();
  QColor color = get_color();
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // SettingInfo *settings = settinginfo();
  // Figure fig = get_figure()->normalize();  // нужен ли указатель?

  // GLuint VBO, VAO, EdgeEBO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // glGenBuffers(1, &EdgeEBO);
  // glBindVertexArray(VAO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, fig.points.size() * sizeof(float),
  //              fig.points.data(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EdgeEBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, fig.edges.size() * sizeof(int),
  //              fig.edges.data(), GL_STATIC_DRAW);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(0); glUseProgram(*shader_program);
  // // glLineWidth(settings->edge_thickness);  // только на старых версиях
  // OpenGL glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glDrawElements(GL_LINES, fig.edges.size() * sizeof(int), GL_UNSIGNED_INT,
  // 0); glDeleteBuffers(1, &VBO); glDeleteBuffers(1, &EdgeEBO);
  // glDeleteVertexArrays(1, &VAO);
}

// void MyOpenGLwindow::resizeGL(int w, int h) {}

void MyOpenGLwindow::setup_Shaders() {
  const char *vertex_shader_src =
      "#version 420 core\n"
      "layout(location = 0) in vec3 pos;\n"
      "void main() {\n"
      "   gl_Position = vec4(pos, 1.0);\n"
      "}\n";

  const char *fragment_shader_src =
      "#version 420 core\n"
      "out vec4 ColorEdges;\n"
      "void main() {\n"
      "   ColorEdges = vec4(0.4, 1.0, 0.4, 1.0);\n"
      "}\n";

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
  glCompileShader(vertex_shader);
  check_shader_compile(vertex_shader, "VERTEX");

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
  glCompileShader(fragment_shader);
  check_shader_compile(fragment_shader, "FRAGMENT");

  *shader_program = glCreateProgram();
  glAttachShader(*shader_program, vertex_shader);
  glAttachShader(*shader_program, fragment_shader);
  glLinkProgram(*shader_program);
  check_program_link(*shader_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void MyOpenGLwindow::check_shader_compile(GLuint shader,
                                          const char *shader_type) {
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
    qCritical() << "ERROR::SHADER::" << shader_type << "::COMPILATION_FAILED\n"
                << infoLog;
    throw std::runtime_error("Shader compilation failed");
  }
}

void MyOpenGLwindow::check_program_link(GLuint program) {
  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
    qCritical() << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog;
    throw std::runtime_error("Program linking failed");
  }
}

QColor MyOpenGLwindow::get_color() {
  SettingInfo *info = settinginfo();
  return (info->background_color && !info->background_color->empty())
             ? QColor(QString::fromStdString(*info->background_color))
             : QColor();
}
