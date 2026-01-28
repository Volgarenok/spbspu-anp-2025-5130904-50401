#ifndef FILE_ARRAY_HPP
#define FILE_ARRAY_HPP
#include <iosfwd>
#include <cstddef>

namespace kuznetsov {
  std::istream& initMatr(std::istream& input, int* mtx, size_t rows, size_t cols);
}

#endif

