#include "figure.h"

Figure::Figure() {
  count_points = 0;
  count_edges = 0;
  min_x = __FLT_MAX__;
  min_y = __FLT_MAX__;
  min_z = __FLT_MAX__;
  max_x = -__FLT_MAX__;
  max_y = -__FLT_MAX__;
  max_z = -__FLT_MAX__;
}

Figure Figure::parce(char* filename) {
  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(filename)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
  }

  auto& attrib = reader.GetAttrib();
  auto& shapes = reader.GetShapes();

  points_file = attrib.vertices;

  for (const auto& shape : shapes) {
    for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
      size_t fv = shape.mesh.num_face_vertices[f];
      for (size_t v = 0; v < fv; v++) {
        tinyobj::index_t idx = shape.mesh.indices[f * fv + v];
        tinyobj::index_t idx_next = shape.mesh.indices[f * fv + (v + 1) % fv];
        edges_file.push_back(idx.vertex_index + 1);
        edges_file.push_back(idx_next.vertex_index + 1);
      }
    }
  }

  return *this;
}

Figure Figure::normalize() {
  ModelInfo* info = modelinfo();

  float x_center = (min_x + max_x) / 2;
  float y_center = (min_y + max_y) / 2;
  float z_center = (min_z + max_z) / 2;

  float scale = (float)((info->scale == 0) ? 1 : info->scale / 100.0) / 1.1;
  float x = (max_x - min_x) / 2;  // x scale
  float y = (max_y - min_y) / 2;  // y scale
  float z = (max_z - min_z) / 2;  // z scale
  if (x == 0) x = 0.01;
  if (y == 0) y = 0.01;
  if (z == 0) z = 0.01;
  scale /= (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);

  for (size_t i = 0; i < points.size(); i += 3) {
    Point point = {points[i], points[i + 1], points[i + 2]};
    point.move(info->trans_x / scale - x_center,
               info->trans_y / scale - y_center,
               info->trans_z / scale - z_center);
    point.rotate(info->rotate_x, info->rotate_y, info->rotate_z);
    point.scale(scale);

    points[i] = point.x;
    points[i + 1] = point.y;
    points[i + 2] = point.z;
  }

  return *this;
}

Figure* get_figure() {
  static Figure fig;
  return &fig;
}