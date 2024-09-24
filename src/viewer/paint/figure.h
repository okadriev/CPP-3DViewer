#ifndef FIGURE_H
#define FIGURE_H

#include <QDebug>  // убрать
#include <vector>

#undef TINYOBJLOADER_IMPLEMENTATION
#include "../obj/tiny_obj_loader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../obj/obj.hpp"
#include "point.h"

class Figure {
 private:
  float min_x, min_y, min_z;
  float max_x, max_y, max_z;

 public:
  std::vector<float> points_file;
  std::vector<unsigned int> edges_file;
  std::vector<float> points;
  std::vector<unsigned int> edges;

  Figure();
  ~Figure();

  void find_min_max_vertices();
  void convert_shapes_to_edges(const std::vector<tinyobj::shape_t> &shapes);
  Figure normalize();
};

Figure *get_figure();
#endif  // FIGURE_H
