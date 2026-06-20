#ifndef ARRAYS_OPERATIONS_HPP
#define ARRAYS_OPERATIONS_HPP

#include "line.hpp"
#include <iosfwd>

namespace khasnulin
{
  const size_t start_length = 10;
  const double capacity_coef = 1.5;
  char *makeStr(size_t size);
  Line *makeLine();
  Line **makeLines(size_t size);
  void clearLines(Line **lines, size_t size);
  void expandLines(Line ***lines, size_t size, size_t newSize);
  char *getResizedStr(const char *str, size_t oldSize, size_t newSize);
  void ensureCapacity(char **str, size_t &size, size_t &capacity);
}

#endif
