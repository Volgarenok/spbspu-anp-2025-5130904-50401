#ifndef ARRAY_FUNCTIONS_HPP
#define ARRAY_FUNCTIONS_HPP
#include <iosfwd>

namespace zharov
{
  std::istream & inputMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);
  void processMatrix(std::ifstream & input, int * matrix, size_t rows, size_t cols, const char * output_file);
}
#endif
