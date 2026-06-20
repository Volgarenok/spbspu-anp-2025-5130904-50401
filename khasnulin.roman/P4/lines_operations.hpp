#ifndef LINES_OPERATIONS_HPP
#define LINES_OPERATIONS_HPP

#include <iosfwd>

namespace khasnulin
{
  const size_t eng_alpabet_size = 26;

  bool isSymbIncluded(const char *str, size_t size, char symb);

  void fillEngAlphabet(char *str);

  char *shrSym(char *result, const char *origin_str, size_t size);
  char *uniTwo(char *result, const char *str1, size_t size1, const char *str2, size_t size2);
}

#endif
