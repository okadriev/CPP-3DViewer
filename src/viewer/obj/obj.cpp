#include "obj.hpp"

#include "model_info.h"
#include "setting_info.h"

ModelInfo* modelinfo() {
  static ModelInfo info;
  return &info;
}

SettingInfo* settinginfo() {
  static SettingInfo info;
  return &info;
}
