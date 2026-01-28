#include "input.hpp"
#include <iostream>
#include "resize.hpp"

char * chernov::getline(std::istream & input, size_t & size, bool (*check_sym)(char), \
  size_t start_size, double k_resize)
{
  bool is_skipws = input.flags() & std::ios_base::skipws;
  if (is_skipws) {
    input >> std::noskipws;
  }
  size_t str_size = start_size, i = 0;
  char * str = nullptr;
  chernov::resize(&str, 0, str_size);
  while (input) {
    if (i >= str_size - 1) {
      size_t new_str_size = str_size * k_resize;
      chernov::resize(&str, str_size, new_str_size);
      if (str == nullptr) {
        free(str);
        return nullptr;
      }
      str_size = new_str_size;
    }
    char ch = '\0';
    input >> ch;
    if (check_sym(ch) || ch == '\0') {
      break;
    }
    str[i] = ch;
    ++i;
  }
  str[i] = '\0';
  size = i;
  if (is_skipws) {
    input >> std::skipws;
  }
  return str;
}

char ** chernov::getlines(std::istream & input, size_t & size, size_t ** sizes, bool (*check_sym)(char), \
  size_t start_size, double k_resize)
{
  size_t strs_size = 0, i = 0;
  size_t * strs_sizes = nullptr;
  char ** strs = nullptr;
  while (input) {
    char * str = nullptr;
    size_t tmp_size = 0;
    str = chernov::getline(input, tmp_size, check_sym, start_size, k_resize);
    if (str == nullptr) {
      destroy(strs, i);
      return nullptr;
    }
    if (!tmp_size) {
      free(str);
      continue;
    }
    chernov::resize(&strs_sizes, strs_size, strs_size + 1);
    chernov::resize(&strs, strs_size, strs_size + 1);
    if (strs_sizes == nullptr || strs == nullptr) {
      free(str);
      free(strs_sizes);
      destroy(strs, i);
      return nullptr;
    }
    ++strs_size;
    strs_sizes[i] = tmp_size;
    strs[i] = str;
    ++i;
  }
  size = strs_size;
  *sizes = strs_sizes;
  return strs;
}
