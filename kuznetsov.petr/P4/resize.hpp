#ifndef EXTENDS_H
#define EXTENDS_H
#include <cstddef>

namespace kuznetsov {
  void extend(char** str, size_t oldSize, size_t newSize);
  void extend(char*** arr, size_t old);
  void extend(size_t** arr, size_t old);
  void cut(char** str, size_t k);
}

#endif

