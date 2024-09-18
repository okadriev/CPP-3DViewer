#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "model_info.h"
#include "setting_info.h"

// перечисление для типа проекции
typedef enum { PARALLEL, CENTER } ProjectionType;
// перечисление для типа отрисовки ребер
typedef enum { SOLID_EDGE, DASHED_EDGE } EdgeType;
// перечисление для типа отрисовки вершин
typedef enum { ZERO, CERCLE, SQUARE } VertexType;

// функция для передачи класса ModelInfo
ModelInfo *modelinfo();
// функция для передачи класса SettingInfo
SettingInfo *settinginfo();
