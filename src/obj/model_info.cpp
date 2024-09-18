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
  Figure fig = get_figure()->parce(*filename.get()); 

  rotate_x = 0;
  rotate_y = 0;
  rotate_z = 0;
  scale = 0;
  trans_x = 0;
  trans_y = 0;
  trans_z = 0;
  num_vertices = fig.points.size() / 3;
  num_edges = fig.edges.size() / 2;
}

