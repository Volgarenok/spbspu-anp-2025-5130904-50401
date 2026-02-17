#ifndef ARR_FUNC_H
#define ARR_FUNC_H

#include <iostream>
namespace zubarev
{
  int getMaxInt();
  int getMinInt();
  std::ostream& outputMatrix(std::ostream& out, const int* matrix, size_t rows, size_t cols);
  int* convertToSquare(int* matrix, size_t& rows, size_t& cols);
  int* readMatrix(std::istream& in, size_t& rows, size_t& cols, int* matrix);
}
#endif
