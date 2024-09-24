#ifndef PARCE_H
#define PARCE_H

#include <iostream>

#include "../paint/figure.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

std::vector<size_t> parse_file(const std::string &filename);

#endif  // PARCE_H