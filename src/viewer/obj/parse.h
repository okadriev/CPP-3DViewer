#ifndef PARCE_H
#define PARCE_H

#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "../paint/figure.h"
#include "tiny_obj_loader.h"

std::vector<size_t> parse_file(std::string &filename);

#endif  // PARCE_H