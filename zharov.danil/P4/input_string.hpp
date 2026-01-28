#ifndef INPUT_STRING_HPP
#define INPUT_STRING_HPP
#include <iosfwd>

namespace zharov
{
  char * getLine(std::istream & in, size_t & len);
  char ** splitLine(char * str, size_t & len, bool(*sep)(char));
}
#endif
