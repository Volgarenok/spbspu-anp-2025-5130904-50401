#include "file_array.hpp"
#include <iostream>
#include <fstream>
#include "variants.hpp"

std::istream& kuznetsov::initMatr(std::istream& input, int* mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; input && i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}


