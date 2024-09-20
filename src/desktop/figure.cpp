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

Figure Figure::parce(std::string& filename) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig config;
  config.triangulate = false;
  if (!reader.ParseFromFile(filename, config)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
  }

  auto& attrib = reader.GetAttrib();
  // qDebug() << " vertices size" << attrib.vertices.size();
  auto& shapes = reader.GetShapes();
  // qDebug() << " shapes size" << shapes.size();

  points_file = attrib.vertices;

  min_x = points_file[0];
  min_y = points_file[1];
  min_z = points_file[2];
  max_x = points_file[0];
  max_y = points_file[1];
  max_z = points_file[2];
  for (size_t i = 0; i < points_file.size(); i += 3) {
    min_x = std::min(min_x, points_file[i]);
    min_y = std::min(min_y, points_file[i + 1]);
    min_z = std::min(min_z, points_file[i + 2]);
    max_x = std::max(max_x, points_file[i]);
    max_y = std::max(max_y, points_file[i + 1]);
    max_z = std::max(max_z, points_file[i + 2]);
  }
  // qDebug() << " points size" << points_file.size();

  for (const auto& shape : shapes) {
    for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
      // qDebug() << " face" << f;
      // qDebug() << " num_face_vertices" << shape.mesh.num_face_vertices[f];
      size_t fv = shape.mesh.num_face_vertices[f];
      for (size_t v = 0; v < fv; v++) {
        tinyobj::index_t idx = shape.mesh.indices[f * fv + v];
        tinyobj::index_t idx_next = shape.mesh.indices[f * fv + (v + 1) % fv];
        edges_file.push_back(idx.vertex_index);
        edges_file.push_back(idx_next.vertex_index);
      }
    }
  }

  points = std::vector<float>(points_file);
  edges = std::vector<int>(edges_file);
  // qDebug() << " edges size" << edges_file.size();

  return *this;
}

Figure Figure::normalize() {
  ModelInfo* info = modelinfo();

  points = std::vector<float>(points_file);
  edges = std::vector<int>(edges_file);

  float x_center = (min_x + max_x) / 2;
  float y_center = (min_y + max_y) / 2;
  float z_center = (min_z + max_z) / 2;
  // qDebug() << "x_center" << x_center;
  // qDebug() << "y_center" << y_center;
  // qDebug() << "z_center" << z_center;

  float scale = (float)(info->scale / 50.0) / 1.1;
  float x = (max_x - min_x) / 2;  // x scale
  float y = (max_y - min_y) / 2;  // y scale
  float z = (max_z - min_z) / 2;  // z scale
  if (x == 0) x = 0.01;
  if (y == 0) y = 0.01;
  if (z == 0) z = 0.01;
  // qDebug() << "x_scale" << x;
  // qDebug() << "y_scale" << y;
  // qDebug() << "z_scale" << z;
  scale /= (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);
  // qDebug() << "scale" << scale;

  for (size_t i = 0; i < points.size(); i += 3) {
    Point point = {points[i], points[i + 1], points[i + 2]};
    // qDebug() << "point " << i << " before" << point.x << point.y << point.z;

    point.move((info->trans_x - 50.0) / 10 / scale - x_center,
               (info->trans_y - 50.0) / 10 / scale - y_center,
               (info->trans_z - 50.0) / 10 / scale - z_center);
    // qDebug() << "point " << i << " move" << point.x << point.y << point.z;
    point.rotate(info->rotate_x, info->rotate_y, info->rotate_z);
    // qDebug() << "point " << i << " rotate" << point.x << point.y << point.z;
    point.scale(scale);
    // qDebug() << "point " << i << " scale" << point.x << point.y << point.z;

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