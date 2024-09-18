#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "../obj/obj.hpp"
#include "tiny_obj_loader.h"
#include "point.h"

class Figure {
 private:
  std::vector<float> points_file;
  std::vector<int> edges_file;
  int count_points;
  int count_edges;
  float min_x;
  float min_y;
  float min_z;
  float max_x;
  float max_y;
  float max_z;

 public:
  std::vector<float> points;
  std::vector<int> edges;
  Figure();
  Figure parce(char *filename);
  Figure normalize();
};

Figure *get_figure();
#endif  // FIGURE_H