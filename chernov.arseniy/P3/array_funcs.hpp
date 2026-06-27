#ifndef ARRAY_FUNCS_HPP
#define ARRAY_FUNCS_HPP

#include <iosfwd>

namespace chernov {
  std::istream & matrixInput(std::istream & input, int * mtx, size_t rows, size_t cols);
  int getSumAntiDiagonal(const int * mtx, size_t x, size_t y, size_t rows, size_t cols);
  int processMatrix(std::istream & input, std::ostream & output, int * matrix, size_t rows, size_t cols);
}

#endif
