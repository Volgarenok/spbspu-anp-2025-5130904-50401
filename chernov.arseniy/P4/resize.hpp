#ifndef RESIZE_HPP
#define RESIZE_HPP

#include <cstddef>

namespace chernov {
  void destroy(char ** strs, size_t k);
  const char * copy(const char * src, char * dest, size_t k);
  void resize(char ** str, size_t old_size, size_t new_size);
  void resize(size_t ** sizes, size_t old_size, size_t new_size);
  void resize(char *** strs, size_t old_size, size_t new_size);
}

#endif
