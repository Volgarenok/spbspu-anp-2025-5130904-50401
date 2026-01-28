#ifndef VARIANTS_HPP
#define VARIANTS_HPP
#include <cstddef>

namespace zharov
{
  bool isUppTriMtx(const int * mtx, size_t rows, size_t cols);
  size_t getCntColNsm(const int * mtx, size_t rows, size_t cols);
}

#endif
