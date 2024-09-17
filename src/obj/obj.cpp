#include "obj.hpp"

void init_setting_info(SettingInfo* info) {
  std::ifstream f(SAVE_SETTINHGS);

  if (f.is_open()) {
    std::string line;

    std::getline(f, line);
    info->projection_type = std::stoi(line);

    std::getline(f, line);
    info->edges_type = std::stoi(line);

    std::getline(f, line);
    info->edge_color = std::make_unique<std::string>(line);

    std::getline(f, line);
    info->edge_thickness = std::stoi(line);

    std::getline(f, line);
    info->background_color = std::make_unique<std::string>(line);

    std::getline(f, line);
    info->vertex_type = std::stoi(line);

    std::getline(f, line);
    info->vertex_color = std::make_unique<std::string>(line);

    std::getline(f, line);
    info->vertex_size = std::stoi(line);

    f.close();
  }
}

void save_settings() {
  SettingInfo* info = settinginfo();
  std::ofstream f(SAVE_SETTINHGS);

  if (f.is_open()) {
    f << info->projection_type << "\n"
      << info->edges_type << "\n"
      << (info->edge_color ? *info->edge_color : "") << "\n"
      << info->edge_thickness << "\n"
      << (info->background_color ? *info->background_color : "") << "\n"
      << info->vertex_type << "\n"
      << (info->vertex_color ? *info->vertex_color : "") << "\n"
      << info->vertex_size;
    f.close();
  }
}

ModelInfo* modelinfo() {
  static ModelInfo info = {0};
  return &info;
}

SettingInfo* settinginfo() {
  static SettingInfo info = {0};
  return &info;
}
