#ifndef LINE_HPP
#define LINE_HPP

#include <iosfwd>

namespace khasnulin
{
  struct Line
  {
    char *str;
    size_t size;
    size_t capacity;
  };
}

#endif
