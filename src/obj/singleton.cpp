#include "obj.hpp"

ModelInfo* modelinfo() {
  static ModelInfo info;
  return &info;
}

SettingInfo* settinginfo() {
  static SettingInfo info;
  return &info;
}
