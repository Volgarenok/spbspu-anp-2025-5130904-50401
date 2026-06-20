#ifndef READ_LINE_HPP
#define READ_LINE_HPP

#include "line.hpp"
#include <iosfwd>

namespace khasnulin
{
  bool isSpace(char ch);

  using filter = bool (*)(char);
  char *getLine(std::istream &in, size_t &size, size_t &capacity, bool &eol, filter check);
  Line *buildLine(std::istream &in, bool &eol, filter check);
  Line **getWordsFromLine(std::istream &in, size_t &size, filter check);
}

#endif
