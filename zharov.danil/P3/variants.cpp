#include "variants.hpp"
#include <algorithm>

bool zharov::isUppTriMtx(const int * mtx, size_t rows, size_t cols)
{
  if (rows != cols) {
    rows = std::min(rows, cols);
    cols = rows;
  }

  if (rows == 0) {
    return false;
  }

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (mtx[cols * i + j] != 0) {
        return false;
      }
    }
  }
  return true;
}

size_t zharov::getCntColNsm(const int * mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }

  size_t res = cols;
  for (size_t i = 0; i < cols; ++i) {
    for (size_t j = 1; j < rows; ++j) {
      if (mtx[j * cols + i] == mtx[(j - 1) * cols + i]) {
        --res;
        break;
      }
    }
  }
  return res;
}
