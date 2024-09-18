#ifndef SETTINGINFO_H
#define SETTINGINFO_H

#include <fstream>
#include <memory>
#include <string>

#include "obj.hpp"

class SettingInfo {
 public:
  SettingInfo();
  void save_settings();

  int projection_type;
  int edges_type;
  std::unique_ptr<std::string> edge_color;
  int edge_thickness;
  std::unique_ptr<std::string> background_color;
  int vertex_type;
  std::unique_ptr<std::string> vertex_color;
  int vertex_size;
};

#endif  // SETTINGINFO_H
