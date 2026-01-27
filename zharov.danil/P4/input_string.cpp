#include "input_string.hpp"
#include <iomanip>
#include "resize.hpp"

char * zharov::getLine(std::istream & in, size_t & len)
{
  size_t size = 10;
  size_t step = 2;
  char end = '\n';
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char * str = new char[size + 1];
  char sym = ' ';
  while (in >> sym && sym != end) {
    if (size == len) {
      try {
        zharov::extendStr(&str, size, size * step);
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
      size *= step;
    }
    str[len] = sym;
    ++len;
  }
  str[len] = '\0';

  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}

char ** zharov::splitLine(char * str, size_t & len, bool(*sep)(char))
{
  size_t size = 10;
  size_t step = 2;
  char ** arr_str = new char * [size];
  bool is_last_sep = true;
  size_t i = 0;
  size_t start_i = 0;
  for (; str[i] != '\0'; ++i) {
    if (len == size) {
      try {
        zharov::extendArr(&arr_str, size, size * step);
      } catch (const std::bad_alloc &) {
        zharov::destroyArr(arr_str, len);
        throw;
      }
      size *= step;
    }
    if (sep(str[i])) {
      if (!is_last_sep) {
        char * new_str = nullptr;
        try {
          new_str = new char[i - start_i + 1];
        } catch (const std::bad_alloc &) {
          zharov::destroyArr(arr_str, len);
          throw;
        }
        for (size_t j = 0; j < i - start_i; ++j) {
          new_str[j] = str[start_i + j];
        }
        new_str[i - start_i] = '\0';
        arr_str[len] = new_str;
        ++len;
        is_last_sep = true;
      }
      start_i = i + 1;
    } else {
      is_last_sep = false;
    }
  }
  if (!is_last_sep || i == 0) {
    char * new_str = nullptr;
    try {
      new_str = new char[i - start_i + 1];
    } catch (const std::bad_alloc &) {
      zharov::destroyArr(arr_str, len);
      throw;
    }
    for (size_t j = 0; j < i - start_i; ++j) {
      new_str[j] = str[start_i + j];
    }
    new_str[i - start_i] = '\0';
    arr_str[len] = new_str;
    ++len;
  }
  return arr_str;
}
