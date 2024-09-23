#ifndef FIGURE_H
#define FIGURE_H

#include <QDebug>  // убрать
#include <iostream>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "../obj/obj.hpp"
#include "point.h"
#include "tiny_obj_loader.h"

class Figure {
 private:
  std::vector<float> points_file;
  std::vector<unsigned int> edges_file;

  unsigned int count_points;
  unsigned int count_edges;
  float min_x, min_y, min_z;
  float max_x, max_y, max_z;

  void find_min_max_vertices();
  void convert_shapes_to_edges(const std::vector<tinyobj::shape_t> &shapes);

 public:
  std::vector<float> points;
  std::vector<unsigned int> edges;

  Figure();
  ~Figure();

  Figure parce(std::string &filename);
  Figure normalize();
};

Figure *get_figure();
#endif  // FIGURE_H
