#ifndef UTILS_HPP
#define UTILS_HPP

#include <iosfwd>

namespace khasnulin
{

  size_t getFirstParameter(const char *num);

  std::istream &readMatrix(std::istream &input, int *arr, size_t n, size_t m, size_t &elems_count);

  std::ostream &printMatrix(std::ostream &output, const int *a, size_t n, size_t m);
}

#endif
