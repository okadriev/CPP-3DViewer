#include "model_info.h"

ModelInfo::ModelInfo() {
  rotate_x = 0;
  rotate_y = 0;
  rotate_z = 0;
  scale = 0;
  trans_x = 0;
  trans_y = 0;
  trans_z = 0;
  num_vertices = 0;
  num_edges = 0;
}

void ModelInfo::zero_model_info() {
  Parametrs *p = get_param();  // ПОТОМ ПОМЕНЯТЬ

  rotate_x = 0;
  rotate_y = 0;
  rotate_z = 0;
  scale = 0;
  trans_x = 0;
  trans_y = 0;
  trans_z = 0;
  num_vertices = p->count_points;
  num_edges = p->count_edges;
}

