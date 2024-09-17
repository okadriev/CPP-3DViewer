#pragma once

#include <fstream>
#include <string>
#include <memory>

#define SAVE_SETTINHGS "../setting.txt"

// структура информации о модели
typedef struct {
  std::unique_ptr<std::string> filename;
  int num_vertices;
  int num_edges;
  double trans_x, trans_y, trans_z;
  double rotate_x, rotate_y, rotate_z;
  int scale;
} ModelInfo;

// структура информации о настройки
typedef struct {
  int projection_type;
  int edges_type;
  std::unique_ptr<std::string> edge_color;
  int edge_thickness;
  std::unique_ptr<std::string> background_color;
  int vertex_type;
  std::unique_ptr<std::string> vertex_color;
  int vertex_size;
} SettingInfo;

// перечисление для типа проекции
typedef enum { PARALLEL, CENTER } ProjectionType;
// перечисление для типа отрисовки ребер
typedef enum { SOLID_EDGE, DASHED_EDGE } EdgeType;
// перечисление для типа отрисовки вершин
typedef enum { ZERO, CERCLE, SQUARE } VertexType;



// Функция для записи настроек в файл
void save_settings();
// функция для передачи структуры ModelInfo
ModelInfo *modelinfo();
// функция для передачи структуры SettingInfo
SettingInfo *settinginfo();
// Функция инициализации SettingInfo
void init_setting_info(SettingInfo *info);