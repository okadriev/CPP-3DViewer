#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <QColor>
#include <QOpenGLWidget>

#include "../viewer/obj/obj.hpp"

class Controller {
 public:
  Controller();
  
  void update_model_info(QString filename);
  void update_model_info(char action, char axis, double value);
  void update_model_info(int scale);

  void update_setting_info(bool push);
  void update_setting_info(QColor color);
  void update_setting_info(bool push, bool solid,
                           std::make_unique<std::string> temp, int value);
  void update_setting_info(bool push, bool zero, bool cercle, bool square,
                           std::make_unique<std::string> temp, int value);
  void update_setting_info(int value);

  void gif_start(QOpenGLWidget* openGLWidget, QString filename);

 private:
  ModelInfo *model_info;
  SettingInfo *setting_info;
};

#endif  // CONTROLLER_H
