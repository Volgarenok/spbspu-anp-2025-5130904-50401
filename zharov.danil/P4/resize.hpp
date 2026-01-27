#ifndef RESIZE_HPP
#define RESIZE_HPP
#include <cstddef>

namespace zharov
{
  void extendArr(char *** str, size_t old_size, size_t new_size);
  void extendStr(char ** str, size_t old_size, size_t new_size);
  void destroyArr(char ** arr, size_t len);
}
#endif
