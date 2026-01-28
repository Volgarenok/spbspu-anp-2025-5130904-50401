#ifndef INPUT_HPP
#define INPUT_HPP

#include <iosfwd>

namespace chernov {
  char * getline(std::istream & input, size_t & size, bool (*check_sym)(char), size_t start_size, double k_resize);
  char ** getlines(std::istream & input, size_t & size, size_t ** sizes, bool (*check_sym)(char), size_t start_size, double k_resize);
}

#endif
