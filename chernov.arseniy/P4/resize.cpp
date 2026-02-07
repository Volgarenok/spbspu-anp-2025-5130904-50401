#include "resize.hpp"
#include <iomanip>

void chernov::destroy(char ** strs, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    free(strs[i]);
  }
  free(strs);
}

const char * chernov::copy(const char * src, char * dest, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    dest[i] = src[i];
  }
  return dest + k;
}

void chernov::resize(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = reinterpret_cast< char * >(malloc(sizeof(char) * new_size));
  if (new_str == nullptr) {
    *str = nullptr;
    return;
  }
  size_t size = std::min(old_size, new_size);
  copy(*str, new_str, size);
  free(*str);
  *str = new_str;
}

void chernov::resize(size_t ** sizes, size_t old_size, size_t new_size)
{
  size_t * new_sizes = reinterpret_cast< size_t * >(malloc(sizeof(size_t) * new_size));
  if (new_sizes == nullptr) {
    *sizes = nullptr;
    return;
  }
  size_t size = std::min(old_size, new_size);
  for (size_t i = 0; i < size; ++i) {
    new_sizes[i] = (*sizes)[i];
  }
  free(*sizes);
  *sizes = new_sizes;
}

void chernov::resize(char *** strs, size_t old_size, size_t new_size)
{
  char ** new_strs = reinterpret_cast< char ** >(malloc(sizeof(char *) * new_size));
  if (new_strs == nullptr) {
    *strs = nullptr;
    return;
  }
  size_t size = std::min(old_size, new_size);
  for (size_t i = 0; i < size; ++i) {
    new_strs[i] = (*strs)[i];
  }
  free(*strs);
  *strs = new_strs;
}
